#include"LeftSideBar.h"

LeftSideBar::LeftSideBar()
{

}

void LeftSideBar::OnAttach()
{
	//create orthographic camera
	gwcEngine::GameObject camera = gwcEngine::Entity::Create("LSB_Camera");
	auto panelCamera = *camera->AddComponent<gwcEngine::Camera>(gwcEngine::CreateRef<gwcEngine::OrthographicCamera>(400, 900));
	camera->AddComponent<gwcEngine::Transform>();
	auto layers = camera->AddComponent<gwcEngine::RenderLayer>();
	layers->RegisterLayer("Left Side Bar");
	layers->ActivateLayer("Left Side Bar");
	panelCamera->SetClearColour({ 1,0,1,1.0 });

	auto panelEnt = gwcEngine::Entity::Create("LSB_Panel");
	auto panel = *panelEnt->AddComponent<gwcEngine::Ref<gwcEngine::Panel>>(gwcEngine::Panel::Create(400, 900));
	panel->SetPosition(200, 450, gwcEngine::Anchor::TopLeft);
	panel->SetCaptureCamera(panelCamera);

}