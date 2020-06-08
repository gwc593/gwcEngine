#pragma once

namespace gwcEngine
{
	class Time
	{
	public:
		inline static void BeginFrame() { return s_Time->BeginFrameImpl(); }
		inline static void EndFrame() { return s_Time->EndFrameImpl(); }
		inline static float GetDeltaTime() { return s_Time->GetDeltaTimeImpl(); }
		inline static float GetTime() { return s_Time->GetTimeImpl(); }
		inline static float GetTimeMS() { return s_Time->GetTimeMsImpl(); }
		inline static Time* GetInstance() { return s_Time; }
		static void Init();

	private:
		virtual void BeginFrameImpl() = 0;
		virtual void EndFrameImpl() = 0;
		virtual float GetDeltaTimeImpl() = 0;
		virtual float GetTimeImpl() = 0;
		virtual float GetTimeMsImpl() = 0;

	private:
		static Time* s_Time;

	};
}