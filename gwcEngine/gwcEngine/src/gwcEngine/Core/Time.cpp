#include"gepch.h"
#include "Time.h"
#include "platform/OpenGL/OpenGLTime.h"
#include "gwcEngine/Renderer/Renderer.h"

namespace gwcEngine
{
	Time* Time::s_Time = nullptr;

	void Time::Init()
	{
		if (Renderer::GetAPI() == RendererAPI::API::OpenGL) {
			s_Time = new OpenGLTime;
			return;
		}

		s_Time = nullptr;
	}

}


