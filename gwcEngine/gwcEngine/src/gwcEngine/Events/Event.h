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

		void subscribe(const Ref<EventCallback<T...>>& callback) const;
		Ref<EventCallback<T...>> subscribe(const std::function<bool(T...)>& callbackFN)const;

		void subscribePriority(const Ref<EventCallback<T...>>& callback)const;
		Ref<EventCallback<T...>>& subscribePriority(std::function<bool(T...)> callbackFN)const;

		void unsubscribe(const Ref < EventCallback<T...>>& callback)const;
		void unsubscribe(const uint32_t& id)const;

		void raiseEvent(T... mArgs) const;

		void operator = (const Event<T...>& D) = delete;


	private:
		mutable std::vector<Ref<EventCallback<T...>>> callbacks;
		mutable int noCallbacks = 0;
	};

	template<typename... T>
	void Event<T...>::subscribe(const Ref<EventCallback<T...>>& callback)const
	{
		callbacks.push_back(callback);
		noCallbacks++;
	}

	template<typename... T>
	Ref<EventCallback<T...>> Event<T...>::subscribe(const std::function<bool(T...)>& callbackFN) const
	{
		
		Ref<EventCallback<T...>> callback = CreateRef< EventCallback<T...>>(callbackFN);

		callbacks.emplace_back(callback);
		//callbacks.push_back(CreateRef<EventCallback<T...>>(new EventCallback<T...>(callbackFN)));
		noCallbacks++;
		
		return callback;
	}

	template<typename... T>
	void Event<T...>::subscribePriority(const Ref<EventCallback<T...>>& callback)const
	{
		callbacks.emplace(callbacks.begin(), callback);
		noCallbacks++;
	}

	template<typename... T>
	Ref<EventCallback<T...>>& Event<T...>::subscribePriority(std::function<bool(T...)> callbackFN) const
	{
		Ref<EventCallback<T...>> callback{ new EventCallback<T...>(callbackFN) };

		callbacks.emplace(callbacks.begin(), callback);
		noCallbacks++;
		return callback;
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const Ref<EventCallback<T...>>& callback) const
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((**it).GetID() == (*callback).GetID()) {
				callbacks.erase(it);
				break;
			}
		}
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const uint32_t& id) const
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((**it).GetID() == id) {
				callbacks.erase(it);
				break;
			}
		}
	}

	template<typename... T>
	void Event<T...>::raiseEvent(T... mArgs) const
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((*it)->GetFunction()(std::forward<T>(mArgs)...)) {
				//terminate propagation of event
				break;
			}
		}
	}
}



