#pragma once
#include"gwcEngine/Core/Time.h"
namespace gwcEngine {

	class OpenGLTime :public Time
	{
	protected:
		virtual void BeginFrameImpl() override;
		virtual void EndFrameImpl() override;
		virtual float GetDeltaTimeImpl() override;
		virtual float GetTimeImpl() override;
		virtual float GetTimeMsImpl() override;

	private:
		float m_TempTime = 0.0f;
		float m_LastFrameTime = 0.0f;
		float m_DeltaTime = 0.0f;
		float m_Time = 0.0f;
	};
}