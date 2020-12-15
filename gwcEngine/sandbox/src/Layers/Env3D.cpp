#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv")
	{
		m_ECS_Manager = gwcEngine::ECSManager::GetInstance();
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

		
	// make camera entity
		auto CameraEnt = m_ECS_Manager->CreateEntity("MainCamera");
		auto CameraComp = *CameraEnt->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f));
		auto CameraTransform = CameraEnt->AddComponent<gwcEngine::Transform>();
		auto RenderLayer = CameraEnt->AddComponent<gwcEngine::RenderLayer>();
		
		//render All Layers
		RenderLayer->ActivateAll();
		//set default colour
		CameraComp->SetClearColour({ 0.65,0.65,0.65,1.0 });


	//make panel entity
		auto testPanel = m_ECS_Manager->CreateEntity("testPanel");
		auto pan = *testPanel->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(1000, 750));
		pan->SetCaptureCamera(CameraComp);


	//make a cube entity 
		auto m_CubeEntity = m_ECS_Manager->CreateEntity("Cube");
		//Add Mesh, transform and material to cube
		auto cubeMesh = m_CubeEntity->AddComponent<gwcEngine::Mesh>();
		auto cubeTransform = m_CubeEntity->AddComponent<gwcEngine::Transform>();
		auto cubeMaterial = m_CubeEntity->AddComponent<gwcEngine::Material>();
		cubeMesh->SetVertexBuffer(verticesCube, sizeof(verticesCube), layoutUnlitShader);
		cubeMesh->SetIndexBuffer(indicesCube, sizeof(indicesCube) / sizeof(uint32_t));
		cubeMaterial->SetShader(m_UnlitColourShader);


	}

	void Env3D::AnimateEntity(gwcEngine::GameObject gameObject, float offset)
	{
		////Make the material change colour with time
		float t = gwcEngine::Time::GetTime()+offset;
		float r = 0.5f * (glm::sin(1.6f * glm::cos(1.0f * t) + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * 1.3f * glm::cos(1.8f * t)) + 1.0f);
		float b = 0.5f * (glm::sin(2.2f * glm::cos(1.4 * t)) + 1.0f);
		gameObject->GetComponent<gwcEngine::Material>()->SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));

		//Move and rotate cube
		//auto cubeTransform = m_ECS_Manager->GetComponent<gwcEngine::Transform>(gameObject);
		//auto xPos = cubeTransform->GetPosition();
		//xPos.x = (3.0f * r - 1.0f);
		//cubeTransform->SetPosition(glm::vec3(r - 0.5f, g - 0.5f, b - 0.5f) * 3.0f);
		//cubeTransform->SetRotation(glm::vec3(r, g, b) * 12.0f);
	}

	void Env3D::OnUpdate()
	{
	///Physics Pipeline
	////////////////////
		//Animate Cube

		AnimateEntity(gwcEngine::Entity::Find("Cube"));

	////Render Pipeline
	///////////////////
	
		auto camera = *gwcEngine::Entity::Find("MainCamera")->GetComponent<gwcEngine::Camera>();
		auto transform = gwcEngine::Entity::Find("MainCamera")->GetComponent<gwcEngine::Transform>();
		transform->SetPosition(transform->GetPosition() + glm::vec3{ 0,0,gwcEngine::Time::GetTime() * 0.5f }*gwcEngine::Time::GetDeltaTime());


		camera->GetFrameBuffer()->Bind();
		gwcEngine::RenderCommand::SetClearColour(camera->GetClearColour());
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(camera);
		m_ECS_Manager->OnUpdate(gwcEngine::Time::GetDeltaTime());
		//unbind perspective camera
		camera->GetFrameBuffer()->Unbind();
		GE_TRACE("FPS = {0}", 1.0f / gwcEngine::Time::GetDeltaTime());

	}
