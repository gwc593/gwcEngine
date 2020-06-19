#pragma once
#include"gwcEngine/ECS/Entity.h"
#include"gwcEngine/ECS/Component.h"

namespace gwcEngine 
{
	class ECSManager
	{
	public:		


		~ECSManager()
		{
			delete s_instance;
		};
	
		
		static ECSManager* GetInstance()
		{
			if (s_instance == nullptr) 
			{
				s_instance = new ECSManager;
			}
			return s_instance; 
		}
	private:

		static ECSManager* s_instance;

		ECSManager()
		{
			Entity::Init();
		}
	};

	
}