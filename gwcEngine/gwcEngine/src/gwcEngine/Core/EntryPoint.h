#pragma once
#include"gepch.h"
#ifdef GE_PLATFORM_WINDOWS

extern gwcEngine::Application* gwcEngine::CreateApplication();

void main(int argc, char** argv)
{
	PROFILE_BEGIN_SESSION("gwcEngineMainThread", "../analysis/gwcEngineMainThread.json");
	
	std::cout << "gwcEngine 0.1" << std::endl;
	
	gwcEngine::Log::Init();
	GE_CORE_INFO("initialised logger!!");

	auto app = gwcEngine::CreateApplication();

	app->Run();
	delete app;

	PROFILE_END_SESSION();
}

#endif // GE_PLATFORM_WINDOWS
