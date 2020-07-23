#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv"),
		m_PCamera(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, 1.78f, 0.1f, 300.0f)), //perspective camera initializer
		m_UICamera(gwcEngine::CreateRef<gwcEngine::OrthographicCamera>()), //perspective camera initializer
		//m_PanelTest(gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), m_UICamera)
		m_ViewPortPanel(800, 600, m_UICamera, m_PCamera)
	{

	}

	void Env3D::OnAttach()
	{
	//setup orthographic camera
		float width = gwcEngine::Application::Get()->GetWindow().GetWidth();
		float height = gwcEngine::Application::Get()->GetWindow().GetHeight();
		float AspecRatio = width / height;
		float AspecRatioInv =  height / width ;
	    //m_UICamera->SetSize(-AspecRatio/2.0f, AspecRatio/2.0f, -1.0/2.0f, 1.0/2.0f);
		m_UICamera->SetAspectRatio(AspecRatio);

		//todo should be assets
		#pragma region CubeMeshData
		gwcEngine::BufferLayout layoutUnlitShader = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"} };

		float verticesCube[8 * 3] = {
			// -----Position-----// -- normal-------- 
				0.5f, 0.5f, 0.5f,
			   -0.5f, 0.5f, 0.5f,
			   -0.5f,-0.5f, 0.5f,
				0.5f,-0.5f, 0.5f,
				0.5f, 0.5f,-0.5f,
			   -0.5f, 0.5f,-0.5f,
			   -0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f
		};
		//f   t   v
		uint32_t indicesCube[6 * 2 * 3] = {
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

	//subscribe frameBuffer and perspective camera to windowSizeChange
		auto& resizeEvent = gwcEngine::Application::Get()->GetWindow().GetWindowResizeEvent();
		//resizeEvent.subscribe((BIND_EVENT_FNO2(gwcEngine::PerspectiveCamera::OnFrameResize, *m_PCamera)));
		resizeEvent.subscribe((BIND_EVENT_FNO2(gwcEngine::Panel::OnMainWindowSizeChange, m_ViewPortPanel)));
		resizeEvent.subscribe((BIND_EVENT_FNO2(gwcEngine::OrthographicCamera::OnScreenResize, *m_UICamera)));

	//entity and components and systems
		//create entity renderer system and register it
		gwcEngine::Ref<gwcEngine::RendererECS> rendSys = gwcEngine::CreateRef<gwcEngine::RendererECS> ("3dRenderer",m_ECS_Manager);
		m_ECS_Manager.RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(rendSys));

	//Compile shaders for use
		m_UnlitColourShader = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");

	//make a cube entity with a mesh, transform and Material
		m_CubeEntity = m_ECS_Manager.CreateEntity("Cube");
		auto& cubeMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(m_CubeEntity);
		auto& cubeTransform = m_ECS_Manager.AddComponent<gwcEngine::Transform>(m_CubeEntity);
		auto& cubeMaterial = m_ECS_Manager.AddComponent<gwcEngine::Material>(m_CubeEntity);
		cubeMesh.SetVertexBuffer(verticesCube, sizeof(verticesCube), layoutUnlitShader);
		cubeMesh.SetIndexBuffer(indicesCube, sizeof(indicesCube) / sizeof(uint32_t));
		cubeMaterial.SetShader(m_UnlitColourShader);
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
		m_ECS_Manager.GetComponent<gwcEngine::Material>(m_CubeEntity).SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));



//Move and rotate cube
		auto& cubeTransform = m_ECS_Manager.GetComponent<gwcEngine::Transform>(m_CubeEntity);
		auto xPos = cubeTransform.GetPosition();
		xPos.x =(2.0f* r -1.0f);
		cubeTransform.SetPosition(glm::vec3(r-1, g-1, b-1)*2.0f);
		cubeTransform.SetRotation(glm::vec3(r, g, b)*8.0f);


//move perspective Camera
		CameraController(m_PCamera);

//Draw 3d Environment renderPass
		m_ViewPortPanel.Bind();
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_PCamera);
		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());
		m_ViewPortPanel.Unbind();

//Draw 2D orthographic UI layer
		m_ViewPortPanel.flush();
		gwcEngine::Renderer::EndScene();
	}
