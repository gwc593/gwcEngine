#pragma once
#include "core.h"
#include "gwcEngine/Events/Event.h"
namespace gwcEngine 
{
	class GE_API Input
	{
	public:
		//polls
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		//events
		inline static Event<int>& GetKeyPressedEvent(){ return s_Instance->m_KeyPressedEvent; }
		inline static Event<int>& GetKeyReleasedEvent(){ return s_Instance->m_KeyReleasedEvent; }

		inline static Event<int>& GetMouseButtonPressedEvent(){ return s_Instance->m_MouseButtonPressedEvent; }
		inline static Event<int>& GetMouseButtonReleasedEvent(){ return s_Instance->m_MouseButtonReleasedEvent; }
		inline static Event<float/*x*/, float/*y*/>& GetMouseMovedEvent(){ return s_Instance->m_MouseMovedEvent; }
		inline static Event<float/*x*/, float/*y*/>& GetMouseScrolledEvent(){ return s_Instance->m_MouseScrolledEvent; }


	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;

		Event<int> m_KeyPressedEvent;
		Event<int> m_KeyReleasedEvent;
		Event<int> m_MouseButtonPressedEvent;
		Event<int> m_MouseButtonReleasedEvent;
		Event<float,float> m_MouseMovedEvent;
		Event<float, float> m_MouseScrolledEvent;

	};
}