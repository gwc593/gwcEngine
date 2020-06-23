#pragma once
#include "ECSTypes.h"
namespace gwcEngine
{

	
	class Entity
	{
		
	public:
		Entity(const std::string& name);
		~Entity();

		Signature GetSignature() const  { return m_Signature; }
		void SetSignature(Signature signature) { m_Signature = signature; }

		const std::string& GetName() const { return m_Name; }

		EntityID GetID()const{return m_ID;}

		//Todo - allow an entity to add a component to itself?
	
	public:


	private:
		EntityID m_ID;
		Signature m_Signature;
		std::string m_Name;


	};


	class EntityManager
	{
	friend class Entity;

	public:
		EntityManager() = default;

		static void Init();

		Entity& FindEntity(const std::string& name)
		{
			auto search = m_Entities.find(name);

			if (search == m_Entities.end()) {
				return *(Entity*)nullptr;
			}

			return *(search->second);
		}

		void DestroyEntity(Entity& entity)
		{
			m_Entities.erase( entity.GetName());
			EntityManager::s_AvailableIDs.push(entity.GetID());
		}

		Ref<Entity> CreateEntity(const std::string& name)
		{
			Ref<Entity> entity{ new Entity(name) };	

			m_Entities.emplace(std::pair(entity->GetName(), entity));
			return entity;
		}

	private:
		static std::queue<EntityID> s_AvailableIDs;
		std::unordered_map<std::string, Ref<Entity>> m_Entities;
		static bool m_init;

	private:
		static EntityID& GetNextID()
		{
			EntityID nextID = s_AvailableIDs.front();
			EntityManager::s_AvailableIDs.pop();
			return nextID;
		}
	};
}