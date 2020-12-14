#pragma once
#include "ECSTypes.h"
namespace gwcEngine
{

	class Application;
	
	class Entity: public std::enable_shared_from_this<Entity>
	{
		
	public:
		Entity(const std::string& name);
		~Entity();

		Signature GetSignature() const  { return m_Signature; }
		void SetSignature(Signature signature) { m_Signature = signature; }

		const std::string& GetName() const { return m_Name; }

		EntityID GetID()const{return m_ID;}

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... mArgs) noexcept
		{
			return Application::Get()->m_ECSManager->AddComponent<T>(shared_from_this(),std::forward<TArgs>(mArgs)...);
		}


		template<typename T>
		T& GetComponent()
		{
			return Application::Get()->m_ECSManager->GetComponent<T>(shared_from_this());
		}


		static Ref<Entity> Find(const std::string name);


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

		Ref<Entity> FindEntity(const std::string& name)
		{
			auto search = m_Entities.find(name);

			if (search == m_Entities.end()) {
				return nullptr;
			}

			return (search->second);
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

	using GameObject = gwcEngine::Ref<gwcEngine::Entity>;
}