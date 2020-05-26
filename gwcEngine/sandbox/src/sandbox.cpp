#include<gwcEngine.h>

//client side implimentation of gwcEngine instance
class Sandbox : public gwcEngine::Application
{
public:
	Sandbox()
	{

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