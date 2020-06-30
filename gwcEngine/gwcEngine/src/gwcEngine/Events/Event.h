#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include <functional>
namespace gwcEngine 
{
	const bool PROPAGATE_EVENT = false;
	const bool TERMINATE_EVENT = true;

	//custom even callbacks always return void
    //customEvent<arg1Type,arg2Type...> myCustomEvent.
	template<typename... T>
	class Event
	{
	private:
		std::vector<std::function<bool(T...)>> callbacks;
		int noCallbacks;

	public:
		void subscribe(std::function<bool(T...)>function);
		void unsubscribe(const std::function<bool(T...)>& function);
		void raiseEvent(T&... mArgs);


		Event();
		~Event();
	};

	template<typename... T>
	void Event<T...>::subscribe(std::function<bool(T...)>function)
	{
		callbacks.push_back(function);
		noCallbacks++;
	}

	template<typename... T>
	void Event<T...>::unsubscribe(const std::function<bool(T...)>& function)
	{
		//todo - impliment method to unsubscribe callback, maybe by reference to an ID returned by the subscribe method?
		for (auto it = callbacks.begin(); it != callbacks.end(); it++) {
			int a=1;
		}
		/*
		auto it = std::find(callbacks.begin(), callbacks.end(), function);
		//
		callbacks.erase(it);
		noCallbacks--;
		*/
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


	template<typename... T>
	Event<T...>::Event()
	{

	}

	template<typename... T>
	Event<T...>::~Event()
	{

	}
}



