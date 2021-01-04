#include"gepch.h"
#include"gwcEngine/Components/Physics/LifeTime.h"
#include "gwcEngine/Core/Time.h"
namespace gwcEngine 
{
	LifeTime::LifeTime(float time) :m_LifeTime(time)
	{
		m_TimeCreated = Time::GetTime();
	}

	const float LifeTime::GetLifeRemaining()
	{
		auto time = Time::GetTime();
		return m_LifeTime - (time - m_TimeCreated);
	}

	void LifeTime::AddTime(float time)
	{
		m_LifeTime += time;
	}

	void LifeTime::RemoveTime(float time)
	{
		m_LifeTime -= time;
	}
}