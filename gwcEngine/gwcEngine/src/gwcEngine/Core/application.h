#pragma once
#include"core.h"
#include"LayerStack.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//to be defined in client
	Application* CreateApplication();
}