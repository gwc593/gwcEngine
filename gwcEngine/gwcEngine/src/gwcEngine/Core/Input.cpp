#include "gepch.h"
#include "Input.h"


namespace gwcEngine
{

	bool Input::s_Dirty = true;
	std::vector<KeyCode>   Input::s_keysDown;
	std::vector<KeyCode>   Input::s_keysUp;
	std::vector<MouseCode> Input::s_MouseBsDown;
	std::vector<MouseCode> Input::s_MouseBsUp;

	Input::Input()
	{


	}
}