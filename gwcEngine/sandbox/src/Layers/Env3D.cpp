#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv"),
		m_PCamera(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f)), //perspective camera initializer
		m_Env3DViewPortPanel(gwcEngine::Panel::Create(1000, 750, m_PCamera))
	{
		//set perspective camera's clear colour
		m_PCamera->SetClearColour({ 0.65,0.65,0.65,1.0 });

		//entity and components and systems
			//create entity renderer system and register it
		gwcEngine::Ref<gwcEngine::RendererECS> rendSys = gwcEngine::CreateRef<gwcEngine::RendererECS>("3dRenderer", m_ECS_Manager);
		m_ECS_Manager.RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(rendSys));
	}

	void Env3D::OnAttach()
	{
		//todo should be assets
		#pragma region CubeMeshData
		gwcEngine::BufferLayout layoutUnlitShader = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"},
			{gwcEngine::ShaderDataType::Float2, "a_UV"},
			{gwcEngine::ShaderDataType::Float3, "a_Norm"}
															 };

		float verticesCube[8 * (3+2+3)] = {
			// -----Position-----// UV Text//--Normal// 
				0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			   -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			   -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			   -0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			   -0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
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

		#pragma region Quad data

		float QuadVer[4 * (3+2+3)] = {
			// -----Position-----// UV Text    //--Normal// 
			 -0.25f,0.25f,0.0,     0.0f,0.0f,  0.0f,0.0f,0.0f,
			-0.25f,-0.25f,0.0,     0.0f,0.0f,  0.0f,0.0f,0.0f,
			 0.25f,-0.25f,0.0,     0.0f,0.0f,  0.0f,0.0f,0.0f,
			 0.25f,0.25f,0.0,      0.0f,0.0f,  0.0f,0.0f,0.0f
		};

		uint32_t QuadInd[2 * 3]{
			0,1,2,
			3,0,2
		};

#pragma endregion

	//Compile shaders for use
		auto m_UnlitColourShader = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");
		auto m_UnlitColourShader2 = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");
		auto m_UnlitColourShader3 = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");

	//make a cube entity 
		m_CubeEntity = m_ECS_Manager.CreateEntity("Cube");
	//Add Mesh, transform and material to cube
		auto& cubeMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(m_CubeEntity);
		auto& cubeTransform = m_ECS_Manager.AddComponent<gwcEngine::Transform>(m_CubeEntity);
		auto& cubeMaterial = m_ECS_Manager.AddComponent<gwcEngine::Material>(m_CubeEntity);
		cubeMesh.SetVertexBuffer(verticesCube, sizeof(verticesCube), layoutUnlitShader);
		cubeMesh.SetIndexBuffer(indicesCube, sizeof(indicesCube) / sizeof(uint32_t));
		cubeMaterial.SetShader(m_UnlitColourShader);

		/*
		auto tempEnt = m_ECS_Manager.CreateEntity("Cube2");
		auto& tempMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(tempEnt);
		auto& tempTran = m_ECS_Manager.AddComponent<gwcEngine::Transform>(tempEnt);
		auto& tempMat = m_ECS_Manager.AddComponent<gwcEngine::Material>(tempEnt);
		tempMesh = cubeMesh;
		tempMat.SetShader(m_UnlitColourShader3);


	//make quad entity
		m_quad = m_ECS_Manager.CreateEntity("Quad");
	//Add Mesh, transform and material to
		auto& quadMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(m_quad);
		auto& quadTransform = m_ECS_Manager.AddComponent<gwcEngine::Transform>(m_quad);
		auto& quadMaterial = m_ECS_Manager.AddComponent<gwcEngine::Material>(m_quad);
		quadMesh.SetVertexBuffer(QuadVer, sizeof(QuadVer), layoutUnlitShader);
		quadMesh.SetIndexBuffer(QuadInd, sizeof(QuadInd) / sizeof(uint32_t));
		quadMaterial.SetShader(m_UnlitColourShader2);
		*/
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

	void Env3D::AnimateEntity(gwcEngine::Ref<gwcEngine::Entity> gameObject, float offset)
	{
		//Make the material change colour with time
		float t = gwcEngine::Time::GetTime()+offset;
		float r = 0.5f * (glm::sin(1.6f * glm::cos(1.0f * t) + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * 1.3f * glm::cos(1.8f * t)) + 1.0f);
		float b = 0.5f * (glm::sin(2.0f * 1.1f * glm::cos(1.4 * t)) + 1.0f);
		m_ECS_Manager.GetComponent<gwcEngine::Material>(gameObject).SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));



		//Move and rotate cube
		auto& cubeTransform = m_ECS_Manager.GetComponent<gwcEngine::Transform>(gameObject);
		auto xPos = cubeTransform.GetPosition();
		xPos.x = (3.0f * r - 1.0f);
		cubeTransform.SetPosition(glm::vec3(r - 0.5f, g - 0.5f, b - 0.5f) * 3.0f);
		cubeTransform.SetRotation(glm::vec3(r, g, b) * 12.0f);
	}


	void Env3D::OnUpdate()
	{
	///Physics Pipeline
	////////////////////
		//Animate Cube
		AnimateEntity(m_CubeEntity);
		//AnimateEntity(m_quad,600.0f);
		//AnimateEntity(m_ECS_Manager.FindEntity("Cube2"),1000.0f);

		//move perspective Camera
		CameraController(m_PCamera);


	////Render Pipeline
	///////////////////
	
		//Render out perspective camera
		m_PCamera->GetFrameBuffer()->Bind();
		gwcEngine::RenderCommand::SetClearColour(m_PCamera->GetClearColour());
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_PCamera);
		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());


		//unbind perspective camera
		m_PCamera->GetFrameBuffer()->Unbind();

	}
