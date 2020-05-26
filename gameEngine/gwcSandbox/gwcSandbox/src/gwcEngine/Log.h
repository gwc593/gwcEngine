#pragma once
#include<memory>
#include"core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace gwcEngine {

	class GE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger ;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//core log macros
#define GE_CORE_TRACE(...)    ::gwcEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)     ::gwcEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)     ::gwcEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)    ::gwcEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_FATAL(...)    ::gwcEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define GE_TRACE(...)    ::gwcEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)     ::gwcEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)     ::gwcEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)    ::gwcEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_FATAL(...)    ::gwcEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
