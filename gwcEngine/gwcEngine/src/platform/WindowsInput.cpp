#include "gepch.h"
#include "WindowsInput.h"
#include"gwcEngine/Core/application.h"
#include<GLFW/glfw3.h>

namespace gwcEngine 
{
	//Todo - this should be OS compile dependent
	Input* Input::s_Instance = new WindowsInput();

	WindowsInput::WindowsInput()
	{

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