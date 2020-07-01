#include"gepch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<glad/glad.h>

namespace gwcEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_windowHandle(windowHandle)
	{
		GE_CORE_ASSERT(windowHandle, "windowHandle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		//initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		GE_CORE_ASSERT(status, "Failed to initialise Glad...");

		GE_CORE_INFO("OpenGL info:");
		GE_CORE_INFO("  Vendor: {0}",glGetString(GL_VENDOR));
		GE_CORE_INFO("  Renderer: {0}",glGetString(GL_RENDERER));
		GE_CORE_INFO("  Version: {0}",glGetString(GL_VERSION));

		//depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		//glDepthFunc(GL_LEQUAL);
		glDepthFunc(GL_LESS);

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}