#include "gepch.h"
#include "Application.h"

#include"gwcEngine/Renderer/Renderer.h"
#include"gwcEngine/Components/System/Panel.h"
#include"gwcEngine/Components/System/Cursor.h"
#include "gwcEngine/Core/Input.h"

//#include"Input.h"

#include<GLFW/glfw3.h>

namespace gwcEngine {

	Application*  Application::s_Instance = nullptr;

	Application::Application()
	{
		//init Application singleton
		s_Instance = this;
		
		//init file system
		auto FS = FileSystem::GetInstance();
		
		//init window
		m_Window = std::unique_ptr<Window>(Window::Create());	
		
		//init time engine
		Time::Init();

		//init ECS manager
		m_ECSManager = ECSManager::GetInstance();

		//init window
		m_Window->SetAppReference(s_Instance);

		Ref<EventCallback<>> windCloseCallback{ new EventCallback<>(BIND_EVENT_FN(Application::OnWindowClose)) };
		s_Instance->GetWindow().GetWindowCloseEvent().subscribe(windCloseCallback);

		Ref<EventCallback<int,int>> windResizeCallback{ new EventCallback<int,int>(BIND_EVENT_FN(Application::OnWindowResize)) };
		s_Instance->GetWindow().GetWindowResizeEvent().subscribe(windResizeCallback);

		//init Cursor
		Cursor::GetInstance();

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
			#if GE_PROFILING
			static bool ProfState = true;
			if (Input::KeyDown(KeyCode::F6)) {
				ProfState = !ProfState;
				::Instrumentor::Get().Enable(ProfState);
			}
			#endif

			if (!m_Minimised) {
				Time::BeginFrame();


				//update layers
				for (Layer* layer : m_LayerStack)
					layer->OnUpdateBase();

				//update ECS
				ECSManager::GetInstance()->OnEarlyUpdate(Time::GetDeltaTime());
				ECSManager::GetInstance()->OnUpdate(Time::GetDeltaTime());

				//gwcEngine::Mesh::Cube();

				RenderCommand::SetClearColour({ 0.1f,0.1f,0.1f,1.0f });
				RenderCommand::Clear();				

				//test();//flushing fucks the quads.
				for (auto panel : Panel::s_Panels) {
					auto pnl = panel.lock();
					if(pnl!= nullptr)
						pnl->flush();
				}
				Renderer::EndScene();
			}
			Input::EndTimeStep();
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