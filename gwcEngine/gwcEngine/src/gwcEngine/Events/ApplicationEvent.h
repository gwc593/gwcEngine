#pragma once

#include"Event.h"

namespace gwcEngine 
{
	class GE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height){}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};


	class GE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowsClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class GE_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(int entered)
			:m_entered(entered){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent::" << m_entered;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

		int m_entered;

	};
}