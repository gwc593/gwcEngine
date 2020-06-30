#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include <functional>
#include "EventCallback.h"


namespace gwcEngine 
{
	const bool PROPAGATE_EVENT = false;
	const bool TERMINATE_EVENT = true;

	//custom even callbacks always return void
    //customEvent<arg1Type,arg2Type...> myCustomEvent.
	template<typename... T>
	class Event
	{
	public:
		Event() = default;
		~Event() = default;

		uint32_t subscribe(const Ref<EventCallback<T...>>& callback);
		uint32_t subscribe(std::function<bool(T...)> callbackFN);

		uint32_t subscribePriority(const Ref<EventCallback<T...>>& callback);
		uint32_t subscribePriority(std::function<bool(T...)> callbackFN);

		void unsubscribe(const Ref < EventCallback<T...>>& callback);
		void unsubscribe(const uint32_t& id);

		void raiseEvent(T&... mArgs);

		void operator = (const Event<T...>& D) = delete;


	private:
		std::vector<Ref<EventCallback<T...>>> callbacks;
		int noCallbacks;
	};

	template<typename... T>
	uint32_t Event<T...>::subscribe(const Ref<EventCallback<T...>>& callback)
	{
		callbacks.push_back(callback);
		noCallbacks++;
		return callback->GetID();
	}

	template<typename... T>
	uint32_t Event<T...>::subscribe(std::function<bool(T...)> callbackFN)
	{
		Ref<EventCallback<T...>> callback{ new EventCallback<T...>(callbackFN) };

		callbacks.push_back(callback);
		noCallbacks++;
		return callback->GetID();
	}

	template<typename... T>
	uint32_t Event<T...>::subscribePriority(const Ref<EventCallback<T...>>& callback)
	{
		callbacks.emplace(callbacks.begin(),callback);
		noCallbacks++;
		return callback->GetID();
	}

	template<typename... T>
	uint32_t Event<T...>::subscribePriority(std::function<bool(T...)> callbackFN)
	{
		Ref<EventCallback<T...>> callback{ new EventCallback<T...>(callbackFN) };

		callbacks.emplace(callbacks.begin(), callback);
		noCallbacks++;
		return callback->GetID();
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const Ref<EventCallback<T...>>& callback)
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((**it).GetID() == (*callback).GetID()){
				callbacks.erase(it);
				break;
			}
		}
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const uint32_t& id)
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((**it).GetID() == id) {
				callbacks.erase(it);
				break;
			}
		}
	}

	template<typename... T>
	void Event<T...>::raiseEvent(T&... mArgs)
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((*it)->GetFunction()(std::forward<T>(mArgs)...)) {
				//GE_CORE_INFO("blocking event processed");
				break;
			}
				
		}
	}
}



