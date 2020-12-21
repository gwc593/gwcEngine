#include"gepch.h"
#include "Entity.h"
#include "gwcEngine/Core/application.h"
namespace gwcEngine
{

	bool EntityManager::m_init = false;

	std::queue<EntityID> EntityManager::s_AvailableIDs{};


	Entity::Entity(const std::string& name)
	{
		m_ID = EntityManager::GetNextID();
		m_Name = name;
		m_isActive = true;
	}

	Entity::~Entity()
	{

	}

	void EntityManager::Init()
	{
		if (!m_init) {
			for (EntityID ent = 0; ent < MAX_ENTITIES; ent++) {
				s_AvailableIDs.push(ent);
			}
			m_init = true;
		}
	}

	Ref<Entity> Entity::Find(const std::string& name)
	{
		return Application::Get()->m_ECSManager->FindEntity(name);;
	}

	bool Entity::MatchesSignature(const Signature& signature)
	{
		Signature result;

		result = signature & m_Signature;

		if (result == signature) {
			return true;
		}
		return false;
	}

	Ref<Entity> Entity::Create(const std::string& name)
	{
		return ECSManager::GetInstance()->CreateEntity(name);
	}
}


