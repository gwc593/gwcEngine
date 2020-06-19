#include"gepch.h"
#include "Entity.h"

namespace gwcEngine
{
	bool Entity::m_init = false;

	std::queue<EntityID> Entity::m_AvailableIDs{};

	std::unordered_map<std::string, EntityID> Entity::m_Entities{};

	Entity::Entity()
	{
		m_ID = m_AvailableIDs.front();
		m_AvailableIDs.pop();
	}

	Entity::~Entity()
	{
		m_AvailableIDs.push(m_ID);
	}

	void Entity::Init()
	{
		if (!m_init) {
			for (EntityID ent = 0; ent < MAX_ENTITIES; ent++) {
				m_AvailableIDs.push(ent);
			}
			m_init = true;
		}
	}

	void Entity::Destroy()
	{
		this->~Entity();
	}
}


