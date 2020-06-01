#include "gepch.h"

#include "Application.h"
#include<GLFW/glfw3.h>
namespace gwcEngine {
	//TODO-GWC understand std::bind
	//TODO-GWC understand std::placeholders

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) 
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);

		//display to consol the event.
		GE_CORE_TRACE("{0}", e.ToString());

		//if the event 'e' is the same type as the template used for Dispatch, then dispatch it using the function bound by the bind event function.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}