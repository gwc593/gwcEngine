#include"gepch.h"
#include"WindowsWindow.h"

#include"gwcEngine/Events/ApplicationEvent.h"
#include"gwcEngine/Events/KeyEvent.h"
#include"gwcEngine/Events/MouseEvent.h"

#include<glad/glad.h>
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
		glfwMakeContextCurrent(m_Window);

		//initialise Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to initialise Glad...");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		//Setup events
		//setGLFW callbacks

		//window resize event
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
								  {
									  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									  WindowResizeEvent event(width, height);

									  data.Width = width;
									  data.Height = height;

									  data.EventCallback(event);
								  });

		//window close event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
								  {
									  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									  WindowCloseEvent event;

									  data.EventCallback(event);
								  });

		//keyboard input callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
						   {
							   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
							   switch (action) 
							   {
									case GLFW_PRESS:
									{
										KeyPressedEvent event(key, 0);
										data.EventCallback(event);
										break;
									}
									   
									case GLFW_REPEAT:
									{
										//TODO GWC - extract repeat count from GLFW
										KeyPressedEvent event(key, 1);
										data.EventCallback(event);
										break;
									}
	
								   case GLFW_RELEASE:
								   {
									   KeyReleasedEvent event(key);
									   data.EventCallback(event);
									   break;
								   }
								}
						   });
						  
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered)
								   {
									   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

									   WindowFocusEvent event(entered);

									   data.EventCallback(event);
								   });

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
								   {
									   switch (action) {
										   case GLFW_PRESS:
										   {
											   WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

											   MouseButtonPressedEvent event(button);

											   Data.EventCallback(event);
											   break;
										   }

										   case GLFW_RELEASE:
										   {
											   WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

											   MouseButtonReleasedEvent event(button);

											   Data.EventCallback(event);
											   break;
										   }
									   }

								   });

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xoffset, (float)yoffset);

			Data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
								 {
									 WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

									 MouseMovedEvent event(xpos, ypos);

									 Data.EventCallback(event);
								 });
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
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