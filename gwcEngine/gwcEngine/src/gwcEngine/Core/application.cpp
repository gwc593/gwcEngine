#include "gepch.h"
#include "Application.h"

#include"gwcEngine/Renderer/Renderer.h"
#include"Input.h"

#include<GLFW/glfw3.h>

namespace gwcEngine {

	Application*  Application::s_Instance = nullptr;

	

	


	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());	
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		
		Time::Init();

		s_Instance = this;

	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		RenderCommand::SetClearColour(glm::vec4(0.15,0.15,0.15,1));
		float time;
		while (m_Running) 
		{
			Time::BeginFrame();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdateBase();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);

		//if the event 'e' is the same type as the template used for Dispatch, then dispatch it using the function bound by the bind event function.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//pass event to layers
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}


}