#include"gepch.h"
#include"WindowsWindow.h"

#include"platform/OpenGL/OpenGLContext.h"
#include"gwcEngine/Components/Cameras/OrthographicCamera.h"

namespace gwcEngine 
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		GE_CORE_ERROR("GLFW Error: ({0}) - {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
	{
		#ifdef GE_PLATFORM_WINDOWS
				return new WindowsWindow(props);
		#endif // GE_PLATFORM_WINDOWS

				return nullptr;
	}



	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
		m_WindowCamera = CreateRef<OrthographicCamera>(GetWidth(), GetHeight());
		auto& resizeEvent = GetWindowResizeEvent();
		resizeEvent.subscribePriority((BIND_EVENT_FNO(gwcEngine::OrthographicCamera::OnScreenResize, m_WindowCamera)));
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;


		GE_CORE_INFO("Creating window {0} ({1},{2})", props.Title, props.Width, props.Height);


		if (!s_GLFWInitialized) {

			int success = glfwInit();
			
			GE_ASSERT(success, "could not initialise GLFW...");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);

		m_Context->Init();



		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		//Setup events
		//setGLFW callbacks

		//window resize event

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
								  {
									  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

									  data.Width = width;
									  data.Height = height;

									  data.app->GetWindow().GetWindowResizeEvent().raiseEvent(width, height);
								  });

		//window close event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
								  {
									  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									  data.app->GetWindow().GetWindowCloseEvent().raiseEvent();
								  });

		//keyboard input callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
						   {
							   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
							   switch (action) 
							   {
									case GLFW_PRESS:
									{
										Input::GetKeyPressedEvent().raiseEvent(key);
										break;
									}
									   
									case GLFW_REPEAT:
									{
										//TODO GWC - extract repeat count from GLFW
										Input::GetKeyPressedEvent().raiseEvent(key);
										break;
									}
	
								   case GLFW_RELEASE:
								   {
									   Input::GetKeyReleasedEvent().raiseEvent(key);
									   break;
								   }
								}
						   });
						  
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered)
								   {
									   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

									   if (entered) {
										   data.app->GetWindow().GetCursorEnterEvent().raiseEvent();
									   }
									   else {
										   data.app->GetWindow().GetCursorExitEvent().raiseEvent();
									   }
								   });

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
								   {
									   switch (action) {
										   case GLFW_PRESS:
										   {
											   Input::GetMouseButtonPressedEvent().raiseEvent(button);
											   break;
										   }

										   case GLFW_RELEASE:
										   {
											   Input::GetMouseButtonReleasedEvent().raiseEvent(button);
											   break;
										   }
									   }

								   });

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
								{
									 Input::GetMouseScrolledEvent().raiseEvent((float&)xoffset, (float&)yoffset);
								});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
								 {
									 float x = (float)xpos;
									 float y = (float)ypos;
									 Input::GetMouseMovedEvent().raiseEvent(x,y);
								 });
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::SwapBuffers()
	{
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		if (enabled) 
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}