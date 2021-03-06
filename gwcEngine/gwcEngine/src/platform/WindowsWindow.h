#pragma once
#include "gwcEngine/core/Window.h"
#include "gwcEngine/core/Input.h"
#include "gwcEngine/Renderer/GraphicsContext.h"

#include<GLFW/glfw3.h>


namespace gwcEngine {
	class Application;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetAppReference(Application* iApp) override { m_Data.app = iApp; }
		void SetVsync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		virtual void SwapBuffers()override;
	
	private:

		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			Application* app;
		};

		WindowData m_Data;
	};
}


