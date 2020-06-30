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

#define BIND_EVENT_FN0(x) std::bind(&x, this)
#define BIND_EVENT_FN1(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_FN2(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_FN3(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_FN4(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_EVENT_FN5(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define BIND_EVENT_FN6(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

#define BIND_EVENT_FNO0(x,y) std::bind(&x, &y)
#define BIND_EVENT_FNO1(x,y) std::bind(&x, &y, std::placeholders::_1)
#define BIND_EVENT_FNO2(x,y) std::bind(&x, &y, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_FNO3(x,y) std::bind(&x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_FNO4(x,y) std::bind(&x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_EVENT_FNO5(x,y) std::bind(&x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define BIND_EVENT_FNO6(x,y) std::bind(&x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)


#define BIND_EVENT_GFN(x) std::bind(x, this, std::placeholders::_1)

#define BIND_EVENT_GFN0(x) std::bind(x, this)
#define BIND_EVENT_GFN1(x) std::bind(x, this, std::placeholders::_1)
#define BIND_EVENT_GFN2(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_GFN3(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_GFN4(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_EVENT_GFN5(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define BIND_EVENT_GFN6(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)
				   
#define BIND_EVENT_GFNO0(x,y) std::bind(x, &y)
#define BIND_EVENT_GFNO1(x,y) std::bind(x, &y, std::placeholders::_1)
#define BIND_EVENT_GFNO2(x,y) std::bind(x, &y, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_GFNO3(x,y) std::bind(x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_GFNO4(x,y) std::bind(x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_EVENT_GFNO5(x,y) std::bind(x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define BIND_EVENT_GFNO6(x,y) std::bind(x, &y, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

#define BIT(x) (1 << x)

namespace gwcEngine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}