#pragma once
#include"core.h"
#include"gwcEngine/Events/Event.h"
#include"gwcEngine/Events/ApplicationEvent.h"
#include"Window.h"

namespace gwcEngine {

	class GE_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined in client
	Application* CreateApplication();
}