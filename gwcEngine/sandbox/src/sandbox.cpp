#include<gwcEngine.h>
#include"gwcEngine/core/EntryPoint.h"
#include<glm/gtc/matrix_transform.hpp>
#include "Layers/Env3D.h"
#include "Layers/LeftSideBar.h"
#include "Layers/DebugCam.h"


//client side implementation of gwcEngine instance
class MainApp : public gwcEngine::Application
{
public:
	MainApp()
	{
		gwcEngine::RenderCommand::SetVsync(true);
		RegisterSystems();
		PushLayer(new Env3D());
		PushLayer(new LeftSideBar());
		PushLayer(new DebugCam());
	}

	~MainApp()
	{

	}

	void RegisterSystems()
	{
		auto m_ECS_Manager = gwcEngine::ECSManager::GetInstance();

		//register LifeTime System
		//TODO make macro
		gwcEngine::Ref<gwcEngine::LifeTimeSystem> lifeTSystem = gwcEngine::CreateRef<gwcEngine::LifeTimeSystem>("LifeTimeSystem");
		m_ECS_Manager->RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(lifeTSystem));

		//Register LineRendering System
		gwcEngine::Ref<gwcEngine::LineRenderingSystem> lineRenderSys = gwcEngine::CreateRef<gwcEngine::LineRenderingSystem>("LineRenderingSystem");
		m_ECS_Manager->RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(lineRenderSys));

		//Register MeshRendering System
		gwcEngine::Ref<gwcEngine::MeshRendererSystem> meshRenderSys = gwcEngine::CreateRef<gwcEngine::MeshRendererSystem>("MeshRendererSystem");
		m_ECS_Manager->RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(meshRenderSys));

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

