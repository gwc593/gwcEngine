#include"DebugCam.h"
void DebugCam::OnAttach()
{



	// make camera entity
	auto CameraEnt = gwcEngine::Entity::Create("DebugCamera");
	auto CameraComp = CameraEnt->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, gwcEngine::Application::Get()->GetWindow().GetWidth(), gwcEngine::Application::Get()->GetWindow().GetHeight(), 0.1f, 10.0f));
	auto CameraTransform = CameraEnt->AddComponent<gwcEngine::Transform>();
	CameraTransform->SetPosition({ 0,0,4 });
	auto RenderLayer = CameraEnt->AddComponent<gwcEngine::RenderLayer>();
	RenderLayer->RegisterLayer("3DScene");
	RenderLayer->ActivateLayer("3DScene");
	RenderLayer->RegisterLayer("Debug");
	RenderLayer->ActivateLayer("Debug");

	CameraTransform->SetRotation({ 0.0f, 0.0f, 0.0F });


	//make panel entity
	auto testPanel = gwcEngine::Entity::Create("DebugPanel");
	auto panTran = testPanel->AddComponent<gwcEngine::Transform>();
	auto pan = *testPanel->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(500, 500, panTran));
	pan->SetPosition(0, 0, gwcEngine::Anchor::TopRight);
	pan->SetCaptureCamera(*CameraComp);

}