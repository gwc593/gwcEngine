#include "gepch.h"
#include "OpenGLTime.h"
#include <GLFW/glfw3.h>

namespace gwcEngine
{

	//Time* Time::s_Time = new OpenGLTime;

	void OpenGLTime::BeginFrameImpl()
	{
		m_TempTime = glfwGetTime();
		m_DeltaTime = m_TempTime-m_LastFrameTime;
		m_LastFrameTime = m_TempTime;
		m_Time += m_DeltaTime;
		
	}

	void OpenGLTime::EndFrameImpl()
	{
		
	}

	float OpenGLTime::GetDeltaTimeImpl()
	{
		return m_DeltaTime;
	}

	float OpenGLTime::GetTimeImpl()
	{
		return m_Time;
	}

	float OpenGLTime::GetTimeMsImpl()
	{
		return m_Time * 1000.0f;
	}

}