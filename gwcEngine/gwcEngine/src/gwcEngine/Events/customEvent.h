#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include <functional>
namespace gwcEngine 
{
	//custom even callbacks always return void
    //customEvent<arg1Type,arg2Type...> myCustomEvent.
	template<typename... T>
	class customEvent
	{
	private:
		std::vector<std::function<void(T...)>> callbacks;
		int noCallbacks;

	public:
		int test;

		void subscribe(std::function<void(T...)>function);
		void unsubscribe(const std::function<void(T...)>& function);
		void raiseEvent(T&&... mArgs);


		customEvent();
		~customEvent();
	};

	template<typename... T>
	void customEvent<T...>::subscribe(std::function<void(T...)>function)
	{
		callbacks.push_back(function);
		noCallbacks++;
	}

	template<typename... T>
	void customEvent<T...>::unsubscribe(const std::function<void(T...)>& function)
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
	void customEvent<T...>::raiseEvent(T&&... mArgs)
	{
		auto it = callbacks.begin();

		for (it; it != callbacks.end(); it++) {
			(*it)(std::forward<T>(mArgs)...);
		}
	}


	template<typename... T>
	customEvent<T...>::customEvent()
	{

	}

	template<typename... T>
	customEvent<T...>::~customEvent()
	{

	}
}



