#include"gepch.h"
#include"System.h"
#include "ECS.h"

namespace gwcEngine
{
	ISystem::ISystem()
	{
		m_ECSManager = ECSManager::GetInstance();
	}
}