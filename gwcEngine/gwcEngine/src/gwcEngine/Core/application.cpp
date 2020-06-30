#include "gepch.h"
#include "Application.h"

#include"gwcEngine/Renderer/Renderer.h"
//#include"Input.h"

#include<GLFW/glfw3.h>

namespace gwcEngine {

	Application*  Application::s_Instance = nullptr;

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());	
		Time::Init();

		s_Instance = this;
		m_Window->SetAppReference(s_Instance);

		m_ECSManager = ECSGlobalManager::GetInstance();

		Ref<EventCallback<>> windCloseCallback{ new EventCallback<>(BIND_EVENT_FN0(Application::OnWindowClose)) };
		s_Instance->GetWindow().GetWindowCloseEvent().subscribe(windCloseCallback);

		Ref<EventCallback<int,int>> windResizeCallback{ new EventCallback<int,int>(BIND_EVENT_FN2(Application::OnWindowResize)) };
		s_Instance->GetWindow().GetWindowResizeEvent().subscribe(windResizeCallback);

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

		while (m_Running) 
		{
			if (!m_Minimised) {
				Time::BeginFrame();

				for (Layer* layer : m_LayerStack)
					layer->OnUpdateBase();
			}

			m_Window->OnUpdate();
		}
	}



	bool Application::OnWindowClose()
	{
		m_Running = false;
		return PROPAGATE_EVENT;
	}

	bool Application::OnWindowResize(int width, int height)
	{
		if (width == 0 || height == 0)
			m_Minimised = true;
		else
			m_Minimised = false;

		Renderer::OnWindowResize(width, height);
		return PROPAGATE_EVENT;
	}


}