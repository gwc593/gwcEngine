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
			for (auto KC : s_keysDown) {
				if (KC == keyCode)
					return true;
			}
			return false;
		};

		virtual bool KeyUpImpl(KeyCode keyCode) override
		{
			for (auto KC : s_keysUp) {
				if (KC == keyCode)
					return true;
			}
			return false;
		};

		virtual bool MouseButtonDownImpl(MouseCode button) override
		{
			for (auto KC : s_MouseBsDown) {
				if (KC == button)
					return true;
			}
			return false;
		};

		virtual bool MouseButtonUpImpl(MouseCode button) override
		{
			for (auto KC : s_MouseBsUp) {
				if (KC == button)
					return true;
			}
			return false;
		};



		bool HandleKeyDown(KeyCode keycode)
		{
			Input::s_keysDown.push_back(keycode);
			Input::s_Dirty = true;
			return PROPAGATE_EVENT;
		}

		bool HandleKeyUp(KeyCode keycode)
		{
			Input::s_keysUp.push_back(keycode);
			Input::s_Dirty = true;
			return PROPAGATE_EVENT;
		}

		bool HandleMBDown(MouseCode button)
		{
			Input::s_MouseBsDown.push_back(button);
			Input::s_Dirty = true;
			return PROPAGATE_EVENT;
		}

		bool HandleMBUp(MouseCode button)
		{
			Input::s_MouseBsUp.push_back(button);
			Input::s_Dirty = true;
			return PROPAGATE_EVENT;
		}


	};
}