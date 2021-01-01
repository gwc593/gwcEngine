#pragma once
#include "gwcEngine/Core/MouseButtonCodes.h"
#include"gwcEngine/Core/Input.h"

namespace gwcEngine
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode keycode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	};
}