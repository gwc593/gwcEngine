#pragma once
#include"gepch.h"
namespace gwcEngine
{
	//Component Constraints
	using ComponentID = uint32_t;
	const ComponentID MAX_COMPONENTS = 32;
	const ComponentID NullComponentID = MAX_COMPONENTS + 10;

	//Entity constraints
	using EntityID = uint32_t;
	const EntityID MAX_ENTITIES = 5000;
	using Signature = std::bitset<MAX_COMPONENTS>;

	//System constraints
	using SystemID = uint32_t;
	const EntityID MAX_SYSTEMS = 100;
}