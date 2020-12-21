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
	//Compile shaders for use
		// Todo - should be stored in a shader library 
		auto m_UnlitColourShader = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");

	// make camera entity
		auto CameraEnt = m_ECS_Manager->CreateEntity("MainCamera");
		auto CameraComp = *CameraEnt->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f));
		auto CameraTransform = CameraEnt->AddComponent<gwcEngine::Transform>();
		CameraTransform->SetPosition({ 0,0,3 });
		auto RenderLayer = CameraEnt->AddComponent<gwcEngine::RenderLayer>();
		RenderLayer->RegisterLayer("3DScene");
		RenderLayer->ActivateLayer("3DScene");


	//make panel entity
		auto testPanel = m_ECS_Manager->CreateEntity("3DPanel");
		auto pan = *testPanel->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(1000, 750));
		pan->SetCaptureCamera(CameraComp);


	//make a cube entity 
		auto m_CubeEntity = m_ECS_Manager->CreateEntity("Cube");
		auto cubeMesh = m_CubeEntity->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Cube());
		auto cubeTransform = m_CubeEntity->AddComponent<gwcEngine::Transform>();
		auto cubeMaterial = m_CubeEntity->AddComponent<gwcEngine::Material>();
		auto meshRend = m_CubeEntity->AddComponent<gwcEngine::MeshRenderer>();

		cubeMaterial->SetShader(m_UnlitColourShader);
		meshRend->ActivateLayer("3DScene");

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
		auto cubeTransform = m_ECS_Manager->GetComponent<gwcEngine::Transform>(gameObject);
		cubeTransform->SetPosition(glm::vec3(r - 0.5f, g - 0.5f, b - 0.5f) * 3.0f);
		cubeTransform->SetRotation(glm::vec3(r, g, b) * 600.0f);
	}

	void Env3D::OnUpdate()
	{
		AnimateEntity(gwcEngine::Entity::Find("Cube"));

		static uint32_t x = gwcEngine::Application::Get()->GetWindow().GetWidth();
		static uint32_t y = gwcEngine::Application::Get()->GetWindow().GetHeight();


		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::KPAdd)) {
		    
			x += 10;
			y += 10;
			auto pan = *(gwcEngine::Entity::Find("MainCamera")->GetComponent<gwcEngine::Camera>());
			pan->SetResolution(x, y);
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::KPSubtract)) {

			x -= 10;
			y -= 10;
			auto pan = *(gwcEngine::Entity::Find("MainCamera")->GetComponent<gwcEngine::Camera>());
			pan->SetResolution(x, y);
		}
	}
