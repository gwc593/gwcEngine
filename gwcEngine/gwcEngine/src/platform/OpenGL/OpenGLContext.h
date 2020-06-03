#pragma once

#include"gwcEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace gwcEngine
{


	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};
}