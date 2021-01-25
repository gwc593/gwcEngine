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
		gwcEngine::RenderCommand::SetVsync(false);
		RegisterSystems();
		PushLayer(new Env3D());
		//PushLayer(new LeftSideBar());
		PushLayer(new DebugCam());
	}

	~MainApp()
	{

	}

	void RegisterSystems()
	{
		LoadModule(LifeTimeSystem, "LifeTimeSystem");
		LoadModule(LineRenderingSystem, "LineRenderingSystem");
		LoadModule(MeshRendererSystem, "MeshRendererSystem");
		LoadModule(CameraSystem, "LifeTimeSystem");
		LoadModule(LightManagerSystem, "LightManagerSystem");
	}
};

//required by EntryPoint.h
gwcEngine::Application* gwcEngine::CreateApplication()
{
	return new MainApp();
}

