#pragma once
#include"gepch.h"
#ifdef GE_PLATFORM_WINDOWS

extern gwcEngine::Application* gwcEngine::CreateApplication();

void main(int argc, char** argv)
{
	std::cout << "gwcEngine 0.1" << std::endl;
	
	gwcEngine::Log::Init();
	GE_CORE_INFO("initialised logger!!");

	auto app = gwcEngine::CreateApplication();

	app->Run();
	delete app;
}

#endif // GE_PLATFORM_WINDOWS
