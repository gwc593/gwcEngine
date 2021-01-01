#pragma once
#include "core.h"
#include "gwcEngine/Events/Event.h"
#include"gwcEngine/Core/KeyCodes.h"
#include"gwcEngine/Core/MouseButtonCodes.h"

namespace gwcEngine 
{
	class GE_API Input
	{
	public:
		//polls
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static bool KeyDown(KeyCode keyCode) { GE_ASSERT(false, "KeyDown is not implemented yet"); return false; }
		inline static bool KeyUp(KeyCode keyCode) { GE_ASSERT(false, "KeyUp is not implemented yet"); return false; }

		inline static bool OnMouseButtonDown(MouseCode button){ GE_ASSERT(false, "OnMouseButtonDown is not implemented yet"); return false; }
		inline static bool OnMouseButtonUp(MouseCode button){ GE_ASSERT(false, "OnMouseButtonReleased is not implemented yet"); return false; }

		//events
		inline static Event<int>& GetKeyPressedEvent(){ return s_Instance->m_KeyPressedEvent; }
		inline static Event<int>& GetKeyReleasedEvent(){ return s_Instance->m_KeyReleasedEvent; }

		inline static Event<int>& GetMouseButtonPressedEvent(){ return s_Instance->m_MouseButtonPressedEvent; }
		inline static Event<int>& GetMouseButtonReleasedEvent(){ return s_Instance->m_MouseButtonReleasedEvent; }
		inline static Event<float/*x*/, float/*y*/>& GetMouseMovedEvent(){ return s_Instance->m_MouseMovedEvent; }
		inline static Event<float/*x*/, float/*y*/>& GetMouseScrolledEvent(){ return s_Instance->m_MouseScrolledEvent; }


	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode keycode) = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		Input();

		static Input* s_Instance;

		Event<int> m_KeyPressedEvent;
		Event<int> m_KeyReleasedEvent;
		Event<int> m_MouseButtonPressedEvent;
		Event<int> m_MouseButtonReleasedEvent;
		Event<float,float> m_MouseMovedEvent;
		Event<float, float> m_MouseScrolledEvent;

		bool m_Dirty = true;

		static std::vector<KeyCode> m_KeyDown;
		static std::vector<KeyCode> m_KeyUp;

		static std::vector<MouseCode> m_MouseDown;
		static std::vector<MouseCode> m_MouseUp;

		static Ref<EventCallback<int>> m_KeyDownCallback;
		//static EventCallback<int> m_KeyUpCallback;

		//static EventCallback<MouseCode> m_MouseDownCallback;
		//static EventCallback<MouseCode> m_MouseUpCallback;

	};
}