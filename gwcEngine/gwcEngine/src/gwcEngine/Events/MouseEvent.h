#pragma once
#include"Event.h"

namespace gwcEngine
{
	class GE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse| EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};


	//TODO- gwc: understand mechanism and then impliment remaining mouse events.
}