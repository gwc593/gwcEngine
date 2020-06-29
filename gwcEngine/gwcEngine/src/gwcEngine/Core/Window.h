#pragma once
#include "gepch.h"
#include"core.h"
#include"gwcEngine/Events/Event.h"
#include "gwcEngine/Core/application.h"

namespace gwcEngine 
{
	class Application;

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "gwcEngine",
					unsigned int width = 1280,
					unsigned int height = 720) :Title(title), Width(width), Height(height){}
	};


	//abstract window interface.
	class GE_API Window
	{
	public:
		virtual ~Window(){}
		
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetAppReference(Application* iApp) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

		//events
		inline Event<int, int>& GetWindowResizeEvent() { return m_windowResizeEvent; }
		inline Event<>& GetWindowCloseEvent() { return m_windowCloseEvent; }

		inline Event<>& GetCursorEnterEvent() { return m_CursorEnter; }
		inline Event<>& GetCursorExitEvent() { return m_CursorExit; }

	private:
		Event<int/*width*/, int/*height*/> m_windowResizeEvent;
		Event<> m_windowCloseEvent;
		Event<> m_CursorEnter;
		Event<> m_CursorExit;
	};
}


