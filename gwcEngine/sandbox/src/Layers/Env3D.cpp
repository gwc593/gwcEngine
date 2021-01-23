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
		// make camera entity
		auto CameraEnt = gwcEngine::Entity::Create("MainCamera");
		auto CameraComp = CameraEnt->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f));
		auto CameraTransform = CameraEnt->AddComponent<gwcEngine::Transform>();

		gwcEngine::ModelLoader::LoadModel("assets/Models/Camera.dae", gwcEngine::ModelFormat::DAE);
		auto CamMesh = gwcEngine::Entity::Find("Camera");
		CamMesh->GetComponent<gwcEngine::MeshRenderer>()->DeactivateAll();
		CamMesh->GetComponent<gwcEngine::MeshRenderer>()->RegisterLayer("Debug");
		CamMesh->GetComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Debug");
		CamMesh->GetComponent<gwcEngine::Transform>()->SetParent(CameraTransform);
		CameraTransform->SetPosition({ 0,0,4.0f });
		auto RenderLayer = CameraEnt->AddComponent<gwcEngine::RenderLayer>();
		RenderLayer->RegisterLayer("Default");
		RenderLayer->ActivateLayer("Default");

		//make panel entity
		auto testPanel = gwcEngine::Entity::Create("3DPanel");
		auto panTran = testPanel->AddComponent<gwcEngine::Transform>();
		auto pan = *testPanel->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(1000, 1000, panTran));
		pan->SetCaptureCamera(*CameraComp);

		//make line entity
		auto lineEnt = gwcEngine::Entity::Create("Line");
		auto tr = lineEnt->AddComponent<gwcEngine::Transform>();
		lineEnt->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Line());
		auto lineRenderer = lineEnt->AddComponent<gwcEngine::LineRenderer>();
		lineRenderer->ActivateLayer("Debug");


		gwcEngine::ModelLoader::LoadModel("assets/Models/Icon.dae", gwcEngine::ModelFormat::DAE);


		//make lights
		auto Bluelight = gwcEngine::Entity::Create("BlueLight");
		Bluelight->AddComponent<gwcEngine::Transform>()->SetPosition({ 1,0,0 });
		Bluelight->GetComponent<gwcEngine::Transform>()->SetScale({ 0.1,0.1,0.1, });
		Bluelight->AddComponent<gwcEngine::Light>()->SetColour({ 0,0,1 });
		Bluelight->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Cube());
		Bluelight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Default");
		Bluelight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Debug");
		Bluelight->AddComponent<gwcEngine::Material>();

		auto Redlight = gwcEngine::Entity::Create("RedLight");
		Redlight->AddComponent<gwcEngine::Transform>()->SetPosition({ 1,0,0 });
		Redlight->GetComponent<gwcEngine::Transform>()->SetScale({ 0.1,0.1,0.1, });
		Redlight->AddComponent<gwcEngine::Light>()->SetColour({ 1,0,0 });
		Redlight->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Cube());
		Redlight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Default");
		Redlight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Debug");
		Redlight->AddComponent<gwcEngine::Material>();

		auto Greenlight = gwcEngine::Entity::Create("GreenLight");
		Greenlight->AddComponent<gwcEngine::Transform>()->SetPosition({ 1,0,0 });
		Greenlight->GetComponent<gwcEngine::Transform>()->SetScale({ 0.1,0.1,0.1, });
		Greenlight->AddComponent<gwcEngine::Light>()->SetColour({ 0,1,0 });
		Greenlight->AddComponent<gwcEngine::Mesh>(gwcEngine::Mesh::Cube());
		Greenlight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Default");
		Greenlight->AddComponent<gwcEngine::MeshRenderer>()->ActivateLayer("Debug");
		Greenlight->AddComponent<gwcEngine::Material>();

	}

	void Env3D::AnimateEntity(gwcEngine::GameObject gameObject, float offset)
	{
		////Make the material change colour with time
		float t = gwcEngine::Time::GetTime()+offset;
		float r = 0.5f * (glm::sin(1.6f * glm::cos(1.0f * t) + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * 1.3f * glm::cos(1.8f * t)) + 1.0f);
		float b = 0.5f * (glm::sin(2.2f * glm::cos(1.4 * t)) + 1.0f);

		//Move and rotate cube
		auto cubeTransform = gameObject->GetComponent<gwcEngine::Transform>();
		cubeTransform->SetPosition(glm::vec3(r - 0.5f, g - 0.5f, b - 0.5f) * 4.0f);
		cubeTransform->SetRotation(glm::vec3(r, g, b) * 600.0f);
	}

	void Env3D::OnUpdate()
	{

		auto hex = gwcEngine::Entity::Find("Icon");

		if (hex != nullptr)
			hex->GetComponent<gwcEngine::Transform>()->SetRotation({ 0,gwcEngine::Time::GetTime() * 120.0f,0 });
			//AnimateEntity(hex,3000);

		static gwcEngine::Ref<gwcEngine::Transform> lineTr = nullptr;

		if (lineTr == nullptr) {
			lineTr = gwcEngine::Entity::Find("Line")->GetComponent<gwcEngine::Transform>();
		}

		if (gwcEngine::Input::IsMouseButtonPressed(gwcEngine::MouseCode::Button1)) {

			//panel ray poistion
			//TODO - NOW ray should be owned by the cursor, panel or camera, or system?
			//     - Ray should be owned by panel, created on mouse over and destroyed on mouse exit.
			auto panel = *(gwcEngine::Entity::Find("3DPanel")->GetComponent<gwcEngine::Ref<gwcEngine::Panel>>());
			auto ray = panel->GetWorldRay(gwcEngine::Input::GetMousePosition());
			lineTr->SetPosition(ray.GetOrigin());
			lineTr->SetScale(glm::normalize(ray.GetDirection())*20000000.0f);
		}

		if (gwcEngine::Input::KeyDown(gwcEngine::KeyCode::S)) {
			gwcEngine::Entity::Find("Icon")->GetComponent<gwcEngine::Material>()->SetValue("u_Colour",glm::vec4(1.0,0,0,1));
		}

		AnimateEntity(gwcEngine::Entity::Find("RedLight"),1000);
		AnimateEntity(gwcEngine::Entity::Find("GreenLight"),10000);
		AnimateEntity(gwcEngine::Entity::Find("BlueLight"),2500);

		
	}
