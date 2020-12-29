#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv")
	{

	}

	void Env3D::OnAttach()
	{

	//Compile shaders for use
		// Todo - should be stored in a shader library 
		auto m_UnlitColourShader = gwcEngine::Shader::Create("assets/Shaders/UnlitColour.glsl");

	// make camera entity
		auto CameraEnt = gwcEngine::Entity::Create("MainCamera");
		auto CameraComp = CameraEnt->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f));
		auto CameraTransform = CameraEnt->AddComponent<gwcEngine::Transform>();
		CameraTransform->SetPosition({ 2,-1,3 });
		CameraTransform->SetRotation({ 30,-40,45.0f });
		auto RenderLayer = CameraEnt->AddComponent<gwcEngine::RenderLayer>();
		RenderLayer->RegisterLayer("3DScene");
		RenderLayer->ActivateLayer("3DScene");
		RenderLayer->RegisterLayer("Debug");
		RenderLayer->ActivateLayer("Debug");


	//make panel entity
		auto testPanel = gwcEngine::Entity::Create("3DPanel");
		auto panTran = testPanel->AddComponent<gwcEngine::Transform>();
		auto pan = *testPanel->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(1000, 750, panTran));
		pan->SetCaptureCamera(*CameraComp);


	//make a cube entity 
		auto m_CubeEntity = gwcEngine::Entity::Create("Cube");
		auto cubeMesh = m_CubeEntity->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Cube());
		auto cubeTransform = m_CubeEntity->AddComponent<gwcEngine::Transform>();
		auto cubeMaterial = m_CubeEntity->AddComponent<gwcEngine::Material>();
		auto meshRend = m_CubeEntity->AddComponent<gwcEngine::MeshRenderer>();
		cubeMaterial->SetShader(m_UnlitColourShader);
		meshRend->ActivateLayer("3DScene");

	//make line entity
		auto lineEnt = gwcEngine::Entity::Create("Line");
		auto tr = lineEnt->AddComponent<gwcEngine::Transform>();
		lineEnt->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Line());
		auto lineRenderer = lineEnt->AddComponent<gwcEngine::LineRenderer>();
		lineRenderer->ActivateLayer("Debug");
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
		auto cubeTransform = gameObject->GetComponent<gwcEngine::Transform>();
		//cubeTransform->SetPosition(glm::vec3(r - 0.5f, g - 0.5f, b - 0.5f) * 3.0f);
		//cubeTransform->SetRotation(glm::vec3(r, g, b) * 600.0f);
	}

	void Env3D::OnUpdate()
	{
		AnimateEntity(gwcEngine::Entity::Find("Cube"));

		static gwcEngine::Ref<gwcEngine::Transform> lineTr = nullptr;

		if (lineTr == nullptr) {
			lineTr = gwcEngine::Entity::Find("Line")->GetComponent<gwcEngine::Transform>();
		}

		static gwcEngine::Ref<gwcEngine::Panel> panel = nullptr;

		if (panel == nullptr) {
			panel = *(gwcEngine::Entity::Find("3DPanel")->GetComponent<gwcEngine::Ref<gwcEngine::Panel>>());
		}


		if (gwcEngine::Input::IsKeyPressed(gwcEngine::KeyCode::LeftControl)) {
			//panel ray poistion
			auto mousePos = gwcEngine::Input::GetMousePosition();
			auto ray = panel->GetWorldRay(mousePos.first, mousePos.second);
			lineTr->SetPosition(ray.GetOrigin());
			lineTr->SetScale(glm::normalize(ray.GetDirection())*2000.0f);

			//GE_TRACE("Ray: pos = ({0},{1},{2}), direction = ({3},{4},{5})", ray.GetOrigin().x, ray.GetOrigin().y, ray.GetOrigin().z, ray.GetDirection().x, ray.GetDirection().y, ray.GetDirection().z);
			//scale line by ray direction
		}

	}
