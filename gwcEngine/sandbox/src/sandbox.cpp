#include<gwcEngine.h>
#include"gwcEngine/core/EntryPoint.h"
#include<glm/gtc/matrix_transform.hpp>
#include "Layers/Env3D.h"

//client side implementation of gwcEngine instance
class MainApp : public gwcEngine::Application
{
public:
	MainApp()
	{
		//gwcEngine::RenderCommand::SetVsync(false);
		RegisterSystems();
		PushLayer(new Env3D());
	}

	~MainApp()
	{

	}

	void RegisterSystems()
	{
		auto m_ECS_Manager = gwcEngine::ECSManager::GetInstance();

		//register Render System
		gwcEngine::Ref<gwcEngine::RendererECS> rendSys = gwcEngine::CreateRef<gwcEngine::RendererECS>("3dRenderer");
		m_ECS_Manager->RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(rendSys));

		//Register CameraSystem
		gwcEngine::Ref<gwcEngine::CameraSystem> camSys = gwcEngine::CreateRef<gwcEngine::CameraSystem>("CameraSystem");
		m_ECS_Manager->RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(camSys));
	}
};

//required by EntryPoint.h
gwcEngine::Application* gwcEngine::CreateApplication()
{
	return new MainApp();
}

