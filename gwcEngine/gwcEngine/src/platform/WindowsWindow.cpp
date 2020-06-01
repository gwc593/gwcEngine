#include"gepch.h"
#include"WindowsWindow.h"

#include"gwcEngine/Events/ApplicationEvent.h"
#include"gwcEngine/Events/KeyEvent.h"
#include"gwcEngine/Events/MouseEvent.h"

namespace gwcEngine 
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		GE_CORE_ERROR("GLFW Error: ({0}) - {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
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

		//window resize event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
								  {
									  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
									  WindowCloseEvent event;

									  data.EventCallback(event);
								  });

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
						   


		//TODO GWC - Impliment Mouse button callbacks https://www.youtube.com/watch?v=r74WxFMIEdU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=12
		//TODO GWC - Impliment Mouse move callbacks https://www.youtube.com/watch?v=r74WxFMIEdU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=12
		//TODO GWC - Impliment Mouse scroll callbacks https://www.youtube.com/watch?v=r74WxFMIEdU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=12
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