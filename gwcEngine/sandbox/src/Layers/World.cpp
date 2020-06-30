#include"World.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	World::World()
		:Layer("3DWorld"),
		m_Camera(58.0, 1.78f, 0.8f, 300.0f) //perspective camera initializer
	{
		//subscribe camera to windowSizeChange
		auto fp = std::bind(&gwcEngine::PerspectiveCamera::OnWindowResize, &m_Camera, std::placeholders::_1, std::placeholders::_2);
		gwcEngine::Application::Get()->GetWindow().GetWindowResizeEvent().subscribe(fp);

		//subscribe to 'P' being pressed
		auto PKeyPressedCallback = std::bind(&World::onPPressed, this, std::placeholders::_1);
		gwcEngine::Input::GetKeyPressedEvent().subscribe(PKeyPressedCallback);


		//initialise mouse//
		mouse = gwcEngine::Input::GetMousePosition();

		//end init mouse

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
			{gwcEngine::ShaderDataType::Float3, "a_Position"}};

		float vertices[8 * 3] = {
		// -----Position-----// -- normal-------- 
			1.0f, 1.0f, 1.0f,     
			0.0f, 1.0f, 1.0f,     
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f
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
		triMesh.SetIndexBuffer(indices, sizeof(indices)/sizeof(uint32_t));

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

	void World::CameraController()
	{
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = m_Camera.GetPostion();
			//Todo, move camera space not world space
			m_Camera.SetPosition({ pos.x, pos.y , pos.z -= 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x -= 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y, pos.z += 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x += 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y += 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y -= 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

	}

	void World::OnUpdate()
	{
		//Make the material change colour with time
		float t = gwcEngine::Time::GetTime();
		float r = 0.5f * (glm::sin(t + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * t) + 1.0f);
		float b = 0.5f * (glm::sin(2.0f * t) + 1.0f);

		auto& material = m_ECS_Manager.GetComponent<gwcEngine::Material>(CubeEntity);
		material.SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));
	
		//move camera (should have ECS control) - TODO
		CameraController();

		//TODO these should be in the rendererECS
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::BeginScene(m_Camera);

		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());

		auto& mesh = m_ECS_Manager.GetComponent<gwcEngine::Mesh>(CubeEntity);

		//gwcEngine::Renderer::Submit(mesh.GetVertexArray(),material.GetShader());

		gwcEngine::Renderer::EndScene();
	}

	bool World::onPPressed(int key)
	{
		if (key == (int)gwcEngine::KeyCode::P)
			GE_TRACE("Key P was pressed");
		return gwcEngine::TERMINATE_EVENT;
	}