#pragma once
#include "gepch.h"
namespace gwcEngine
{

	class IEventCallback
	{
	public:
		static uint32_t GetNextID() { return s_NextID++; }
		virtual ~IEventCallback() = default;
	private:
		IEventCallback() = default;
		static uint32_t s_NextID;

	};


	template<typename ...T>
	class EventCallback
	{
	public:
		EventCallback()
		{
			m_ID = IEventCallback::GetNextID();
		}


		EventCallback(EventCallback&& other) noexcept
		{
			m_ID = other.m_ID;
			m_Callback = other.m_Callback;
		}

		EventCallback(const EventCallback& other)
		{
			m_ID = other.m_ID;
			m_Callback = other.m_Callback;
		}

		void SetCallback(std::function<bool(T...)> callbackFunction)
		{
			m_Callback = callbackFunction;
		}

		EventCallback(std::function<bool(T...)> callbackFunction)
		{
			m_ID = IEventCallback::GetNextID();
			m_Callback = callbackFunction;
		}

		~EventCallback() 
		{

		};

		uint32_t GetID() { return m_ID; }
		std::function<bool(T...)>& GetFunction() { return m_Callback; }

	private:

		uint32_t m_ID;
		std::function<bool(T...)> m_Callback;
	};
	
}