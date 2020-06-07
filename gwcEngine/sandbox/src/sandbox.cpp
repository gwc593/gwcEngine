#include<gwcEngine.h>


class Target : public gwcEngine::Layer
{
public:
	Target()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (gwcEngine::Input::IsKeyPressed(GE_KEY_TAB))
		{
			//GE_INFO("Tab is pressed");
		}
	}

	bool OnClick(gwcEngine::Event& e)
	{
		
		if (e.GetEventType() == gwcEngine::EventType::MouseButtonPressed) {
			gwcEngine::MouseButtonPressedEvent& event = (gwcEngine::MouseButtonPressedEvent&)e;
			if (event.GetButton() == (int)gwcEngine::MouseCode::Button0) {
				GE_TRACE("screen clicked!");
				return true;
			}
		}
		
		return false;
	}

	void OnEvent(gwcEngine::Event& event) override
	{
		//GE_TRACE(event.ToString());
		gwcEngine::EventDispatcher dp(event);
		dp.Dispatch<gwcEngine::MouseButtonPressedEvent>(BIND_EVENT_FN(Target::OnClick));
	}
};




//client side implimentation of gwcEngine instance
class Sandbox : public gwcEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new Target());
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