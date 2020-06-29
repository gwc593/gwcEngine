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

		auto windowCloseCallback = std::bind(&Application::OnWindowClose, this);
		s_Instance->GetWindow().GetWindowCloseEvent().subscribe(windowCloseCallback);
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
			Time::BeginFrame();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdateBase();

			m_Window->OnUpdate();
		}
	}



	void Application::OnWindowClose()
	{
		m_Running = false;
	}


}