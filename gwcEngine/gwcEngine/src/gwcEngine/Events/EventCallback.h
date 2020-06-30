#pragma once
#include "gepch.h"
namespace gwcEngine
{

	class IEventCallback
	{
	public:
		static uint32_t GetNextID(){ return s_NextID++; }
		virtual ~IEventCallback() = default;
	private:
		IEventCallback() = default;
		static uint32_t s_NextID;
		
	};


	template<typename ...T>
	class EventCallback: public IEventCallback
	{
	public:
		EventCallback(std::function<bool(T...)> callbackFunction)
		{
			m_ID = GetNextID();
			m_Callback = callbackFunction;
		}

		virtual ~EventCallback() = default;

	private:
		
		uint32_t m_ID;
		std::function<bool(T...)> m_Callback;
	};
}