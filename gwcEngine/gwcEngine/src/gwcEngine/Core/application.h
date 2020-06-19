#pragma once
#include"core.h"
#include"Window.h"
#include"LayerStack.h"
#include"gwcEngine/Events/Event.h"
#include"gwcEngine/Events/ApplicationEvent.h"

//ECS DEV WIP
#include"gwcEngine/ECS/ECS.h"

#include "Time.h"

namespace gwcEngine {

	class GE_API Application
	{
	public:
		ECSManager* m_ECSManager;
	public:
		Application();
		virtual ~Application();
		
		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }


		inline static Application* Get() { return s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:


		static Application* s_Instance;

		

	};

	//to be defined in client
	Application* CreateApplication();
}