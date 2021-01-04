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
		friend class Window;
		virtual ~Input() = default;

		//polls
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static bool KeyDown(KeyCode keyCode) { return s_Instance->KeyDownImpl(keyCode); }
		inline static bool KeyUp(KeyCode keyCode) { return s_Instance->KeyUpImpl(keyCode); }

		inline static bool MouseButtonDown(MouseCode button) { return s_Instance->MouseButtonDownImpl(button); }
		inline static bool MouseButtonUp(MouseCode button) { return s_Instance->MouseButtonUpImpl(button); }

		//events
		inline static const Event<int>& GetKeyPressedEvent() { return Input::m_KeyPressedEvent; }
		inline static const Event<int>& GetKeyReleasedEvent() { return Input::m_KeyReleasedEvent; }

		inline static const Event<int>& GetMouseButtonPressedEvent() { return Input::m_MouseButtonPressedEvent; }
		inline static const Event<int>& GetMouseButtonReleasedEvent() { return Input::m_MouseButtonReleasedEvent; }

		inline static const Event<float/*x*/, float/*y*/>& GetMouseMovedEvent() { return Input::m_MouseMovedEvent; }

		inline static const Event<float/*x*/, float/*y*/>& GetMouseScrolledEvent() { return Input::m_MouseScrolledEvent; }

		inline static void EndTimeStep() 
		{
			PROFILE_FUNCTION();
			if (s_Dirty) {
				s_keysDown.clear();  
				s_keysUp.clear();
				s_MouseBsDown.clear();
				s_MouseBsUp.clear();
				s_Dirty = false;
			}
		}

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode keycode) = 0;

		virtual bool KeyDownImpl(KeyCode keyCode) = 0;
		virtual bool KeyUpImpl(KeyCode keyCode) = 0;
		virtual bool MouseButtonDownImpl(MouseCode button) = 0;
		virtual bool MouseButtonUpImpl(MouseCode button) = 0;


		virtual std::pair<float,float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		Input();

		static Input* s_Instance;

		static Event<int> m_KeyPressedEvent;
		static Event<int> m_KeyReleasedEvent;
		static Event<int> m_MouseButtonPressedEvent;
		static Event<int> m_MouseButtonReleasedEvent;
		static Event<float,float> m_MouseMovedEvent;
		static Event<float, float> m_MouseScrolledEvent;

		static bool s_Dirty;
		static std::vector<KeyCode> s_keysDown;
		static std::vector<KeyCode> s_keysUp;
		static std::vector<MouseCode> s_MouseBsDown;
		static std::vector<MouseCode> s_MouseBsUp;


	};
}