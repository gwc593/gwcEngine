#pragma once
#include"core.h"

namespace gwcEngine {

	class GE_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();

	};

	//to be defined in client
	Application* CreateApplication();
}


