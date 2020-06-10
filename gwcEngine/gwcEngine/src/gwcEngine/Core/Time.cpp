#include"gepch.h"
#include "Time.h"
#include "platform/OpenGL/OpenGLTime.h"
#include "gwcEngine/Renderer/Renderer.h"

namespace gwcEngine
{
	Time* Time::s_Time = nullptr;

	void Time::Init()
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::OpenGL:
			{
				s_Time = new OpenGLTime;
				return;
			}

			case RendererAPI::API::None:
			{
				GE_CORE_ASSERT(false, "No rendering API selected...");
				s_Time = nullptr;
				return;
			}
		}


		GE_CORE_ASSERT(false, "Invalid rendering API selected...");
		s_Time = nullptr;
	}

}


