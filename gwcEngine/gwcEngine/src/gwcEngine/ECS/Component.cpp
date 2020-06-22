#include "gepch.h"
#include "Component.h"

namespace gwcEngine
{
	
	ComponentID ComponentManager::s_NextID = 0;

	std::unordered_map<std::string, ComponentID> ComponentManager::s_ComponentIDs{};
	
}


