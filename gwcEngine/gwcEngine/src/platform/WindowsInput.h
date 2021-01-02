#pragma once
#include "gwcEngine/Core/MouseButtonCodes.h"
#include"gwcEngine/Core/Input.h"

namespace gwcEngine
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		virtual ~WindowsInput() = default;

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode keycode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual bool KeyDownImpl(KeyCode keyCode) override 
		{ 
			for (auto KC : m_keyDown) {
				if (KC == keyCode)
					return true;
			}
			return false;
		};

		virtual bool KeyUpImpl(KeyCode keyCode) override
		{
			for (auto KC : m_keyUp) {
				if (KC == keyCode)
					return true;
			}
			return false;
		};

		virtual bool MouseButtonDownImpl(MouseCode button) override
		{
			for (auto KC : m_MouseDown) {
				if (KC == button)
					return true;
			}
			return false;
		};

		virtual bool MouseButtonUpImpl(MouseCode button) override
		{
			for (auto KC : m_MouseUp) {
				if (KC == button)
					return true;
			}
			return false;
		};



		bool HandleKeyDown(KeyCode keycode)
		{
			Input::m_keyDown.push_back(keycode);
			return PROPAGATE_EVENT;
		}

		bool HandleKeyUp(KeyCode keycode)
		{
			Input::m_keyUp.push_back(keycode);
			return PROPAGATE_EVENT;
		}

		bool HandleMBDown(MouseCode button)
		{
			Input::m_MouseDown.push_back(button);
			return PROPAGATE_EVENT;
		}

		bool HandleMBUp(MouseCode button)
		{
			Input::m_MouseUp.push_back(button);
			return PROPAGATE_EVENT;
		}


	};
}