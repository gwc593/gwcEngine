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
		ECSManager* m_ECSManager;


	public:
		Application();
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		//find layer by name or template type.
		template<typename T>
		T& FindLayer(const std::string& name) { return *(T*)s_Instance->m_LayerStack.GetLayer(name); }
		Layer* FindLayer(const std::string& name) { return s_Instance->m_LayerStack.GetLayer(name); }


		Window& GetWindow() { return *m_Window; }


		inline static Application* Get() { return s_Instance; }
	private:
		bool OnWindowClose();
		bool OnWindowResize(int width, int height);
	
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		bool m_Minimised = false;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();
}