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

		void subscribe(std::function<bool(T...)>function);
		void unsubscribe(const std::function<bool(T...)>& function);
		void raiseEvent(T&... mArgs);

	private:
		std::vector<std::function<bool(T...)>> callbacks;
		int noCallbacks;
	};

	template<typename... T>
	void Event<T...>::subscribe(std::function<bool(T...)>function)
	{
		callbacks.push_back(function);
		noCallbacks++;
	}


	//utility function to compare where stdFunction is pointing
	template<typename... T>
	size_t getAddress(const std::function<bool(T...)> f)
	{
		//auto fnPointer = f.target<bool(T...)>();
		auto fnPointer = f.target<bool(T...)>();
		return (size_t)*fnPointer;
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const std::function<bool(T...)>& function)
	{
		//todo - impliment method to unsubscribe callback, maybe by reference to an ID returned by the subscribe method?
		
		auto functionCopy = function;
		
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {

		}
	}

	template<typename... T>
	void Event<T...>::raiseEvent(T&... mArgs)
	{
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			if ((*it)(std::forward<T>(mArgs)...)) {
				//GE_CORE_INFO("blocking event processed");
				break;
			}
				
		}
	}
}



