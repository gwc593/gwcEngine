#pragma once
namespace gwcEngine 
{
	class LifeTime
	{
	public:
		LifeTime(float time);
		const float GetLifeRemaining();
		void AddTime(float time);
		void RemoveTime(float time);

	private:
		float m_LifeTime;
		float m_TimeCreated;
	};
}