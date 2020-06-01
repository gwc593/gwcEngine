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


	class GE_API MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button)
			:m_Button(button){}
		
		inline int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		int m_Button;
	};

	class GE_API MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int button)
			:m_Button(button)
		{
		}

		inline int GetButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		int m_Button;
	};


	class GE_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y)
			:m_OffsetX(x), m_OffsetY(y){}


		inline float GetXOffset() const { return m_OffsetX; }
		inline float GetYOffset() const { return m_OffsetY; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScroll: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:

		float m_OffsetX, m_OffsetY;
	};
}