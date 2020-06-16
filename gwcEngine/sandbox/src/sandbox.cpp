#include<gwcEngine.h>
#include"gwcEngine/core/EntryPoint.h"
#include<glm/gtc/matrix_transform.hpp>
#include "World.h"

//client side implementation of gwcEngine instance
class Sandbox : public gwcEngine::Application
{
public:
	Sandbox()
	{
		//gwcEngine::RenderCommand::SetVsync(false);
		PushLayer(new World());
	}

	~Sandbox()
	{

	}
};

//required by EntryPoint.h
gwcEngine::Application* gwcEngine::CreateApplication()
{
	return new Sandbox();
}