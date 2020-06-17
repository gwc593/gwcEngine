#include<gwcEngine.h>
#include"gwcEngine/core/EntryPoint.h"
#include<glm/gtc/matrix_transform.hpp>
#include "Layers/World.h"

//client side implementation of gwcEngine instance
class MainApp : public gwcEngine::Application
{
public:
	MainApp()
	{
		//gwcEngine::RenderCommand::SetVsync(false);
		PushLayer(new World());
	}

	~MainApp()
	{

	}
};

//required by EntryPoint.h
gwcEngine::Application* gwcEngine::CreateApplication()
{
	return new MainApp();
}