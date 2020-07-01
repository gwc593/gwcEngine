#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv"),
		m_PCamera(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, 1.78f, 0.8f, 300.0f)), //perspective camera initializer
		m_UICamera(gwcEngine::CreateRef<gwcEngine::OrthographicCamera>(-1.6,1.6,-0.9,0.9)) //perspective camera initializer
	{
		

	}

	void Env3D::OnAttach()
	{
		gwcEngine::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_FrameBuffer = gwcEngine::FrameBuffer::Create(fbSpec);




		//subscribe camera to windowSizeChange
		auto& resizeEvent = gwcEngine::Application::Get()->GetWindow().GetWindowResizeEvent();
		resizeEvent.subscribe((BIND_EVENT_FNO2(gwcEngine::PerspectiveCamera::OnWindowResize, *m_PCamera)));

		//subscribe to 'P' being pressed
		gwcEngine::Input::GetKeyPressedEvent().subscribe(BIND_EVENT_FN1(Env3D::onPPressed));
		uint32_t idUI = gwcEngine::Input::GetKeyPressedEvent().subscribePriority(BIND_EVENT_FN1(Env3D::onPPressedUI));
		gwcEngine::Input::GetKeyPressedEvent().subscribe(BIND_EVENT_FN1(Env3D::onPPressed));


		//entity and components and systems
		gwcEngine::Ref<gwcEngine::RendererECS> rendSys{ new gwcEngine::RendererECS("3dRenderer",m_ECS_Manager) };
		m_ECS_Manager.RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(rendSys));

		CubeEntity = m_ECS_Manager.CreateEntity("Cube");
		auto& triMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(CubeEntity);
		auto& transform = m_ECS_Manager.AddComponent<gwcEngine::Transform>(CubeEntity);
		auto& t_Mat = m_ECS_Manager.AddComponent<gwcEngine::Material>(CubeEntity);
		//TODO add camera reference.

#pragma region CubeMeshData
		gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"} };

		float vertices[8 * 3] = {
			// -----Position-----// -- normal-------- 
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				-0.5f, -0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,
				0.5f, 0.5f, -0.5f,
				-0.5f, 0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				0.5f, -0.5f, -0.5f
		};

		uint32_t indices[6 * 3 * 2] = {
			0,1,2,
			0,2,3,
			4,1,0,
			4,5,1,
			4,5,6,
			4,6,7,
			1,5,6,
			1,6,2,
			0,3,7,
			4,0,7,
			7,6,2,
			7,2,3 };

#pragma endregion


		triMesh.SetVertexBuffer(vertices, sizeof(vertices), layout);
		triMesh.SetIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));

#pragma region unlitFlatShaderSrc
		//create a basic shader
		std::string unlitColourvertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
				v_Position = a_Position;
			}
		)";

		std::string unlitColourfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			uniform vec4 u_Colour;

			in vec3 v_Position;

			void main()
			{
				color = u_Colour;
			}
		)";

#pragma endregion

		m_UnlitColourShader.reset(gwcEngine::Shader::Create(unlitColourvertexSrc, unlitColourfragmentSrc));

		t_Mat.SetShader(m_UnlitColourShader);
	}

	void Env3D::CameraController(gwcEngine::Ref<gwcEngine::Camera> camera)
	{
		auto pCamera = std::dynamic_pointer_cast<gwcEngine::PerspectiveCamera>(m_PCamera);
		
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = camera->GetPostion();
			//Todo, move camera space not world space
			camera->SetPosition({ pos.x, pos.y , pos.z -= 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x -= 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y, pos.z += 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x += 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y += 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y -= 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

	}

	void Env3D::OnUpdate()
	{
//Make the material change colour with time
		float t = gwcEngine::Time::GetTime();
		float r = 0.5f * (glm::sin(t + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * t) + 1.0f);
		float b = 0.5f * (glm::sin(2.0f * t) + 1.0f);
		m_ECS_Manager.GetComponent<gwcEngine::Material>(CubeEntity).SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));
	
//move perspective Camera
		CameraController(m_PCamera);

//Draw 3d Environment renderPass
		m_FrameBuffer->Bind();
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_PCamera);
		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());
		m_FrameBuffer->Unbind();
		gwcEngine::Renderer::EndScene();

//Draw 2D orthographic UI layer
		//todo tomorrow!!! implement texture class with blending....
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_PCamera);
		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());

		
	}

	bool Env3D::onPPressed(int key)
	{
		if (key == (int)gwcEngine::KeyCode::P)
			GE_TRACE("Key P was pressed");
		return gwcEngine::PROPAGATE_EVENT;
	}

	bool Env3D::onPPressedUI(int key)
	{
		if (key == (int)gwcEngine::KeyCode::P)
			GE_TRACE("UI - Key P was pressed");
		return gwcEngine::TERMINATE_EVENT;
	}