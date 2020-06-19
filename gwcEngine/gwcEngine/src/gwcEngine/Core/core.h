#pragma once
#include<memory>
#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define GE_API __declspec(dllexport)
		#else
			#define GE_API __declspec(dllimport)
		#endif // GE_BUILD_DLL
	#else
		#define GE_API
	#endif	
#else
	#error gwcEngine only supports windows at the moment.
#endif // GE_PLATFORM_WINDOWS

#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...) 
	#define GE_CORE_ASSERT(x, ...) 
#endif // GE_ENABLE_ASSERTS


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_GFN(x) std::bind(x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace gwcEngine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}