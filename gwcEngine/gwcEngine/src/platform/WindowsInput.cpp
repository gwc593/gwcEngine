#include "gepch.h"
#include "WindowsInput.h"
#include"gwcEngine/Core/application.h"
#include<GLFW/glfw3.h>

namespace gwcEngine 
{
	//Todo - these static definitions should not be here, this is required until the next todo is fixed....
	Event<int> Input::m_KeyPressedEvent;
	Event<int> Input::m_KeyReleasedEvent;
	Event<int> Input::m_MouseButtonPressedEvent;
	Event<int> Input::m_MouseButtonReleasedEvent;
	Event<float, float> Input::m_MouseScrolledEvent;
	Event<float, float> Input::m_MouseMovedEvent;

	//Todo - this should be OS compile dependent
	Input* Input::s_Instance = new WindowsInput();

	WindowsInput::WindowsInput()
	{
		//Input::m_KeyPressedEvent.subscribe([this](int keycode) {return this->HandleKeyDown((KeyCode)keycode); });
		Input::m_KeyPressedEvent.subscribe([this](int keycode) {return this->HandleKeyDown((KeyCode)keycode); });
		Input::m_KeyReleasedEvent.subscribe([this](int keycode) {return this->HandleKeyUp((KeyCode)keycode); });

		Input::m_MouseButtonPressedEvent.subscribe([this](int keycode) {return this->HandleMBDown((MouseCode)keycode); });
		Input::m_MouseButtonReleasedEvent.subscribe([this](int keycode) {return this->HandleMBUp((MouseCode)keycode); });
	}

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, (int)keycode);

		
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		double pos;
		glfwGetCursorPos(window, &pos, nullptr);

		return (float)pos;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		double pos;
		glfwGetCursorPos(window, nullptr, &pos);

		return (float)pos;
	}

	std::pair<float,float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos,(float)ypos };
	}
}