#pragma once
#include"core.h"
#include"LayerStack.h"
#include "gwcEngine/Events/Event.h"
#include"gwcEngine/ECS/ECS.h"
#include "Time.h"
#include"Window.h"

namespace gwcEngine {
	class Window;
	class GE_API Application
	{
	public:
		ECSGlobalManager* m_ECSManager;


	public:
		Application();
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }




		inline static Application* Get() { return s_Instance; }
	private:
		void OnWindowClose();
	
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		//Application Events


	private:


		static Application* s_Instance;

		

	};

	//to be defined in client
	Application* CreateApplication();
}