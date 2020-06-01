#include<gwcEngine.h>

class ExampleLayer : public gwcEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//GE_INFO("ExampleLayer::Update");
	}

	void OnEvent(gwcEngine::Event& event) override
	{
		GE_TRACE("{0}", event.ToString());
	}
};


//client side implimentation of gwcEngine instance
class Sandbox : public gwcEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
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