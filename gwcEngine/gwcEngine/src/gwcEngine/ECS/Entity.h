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
		Ref<T> AddComponent(TArgs&&... mArgs) noexcept
		{
			return ECSManager::GetInstance()->AddComponent<T>(shared_from_this(),std::forward<TArgs>(mArgs)...);
		}


		template<typename T>
		Ref<T> GetComponent()
		{
			return ECSManager::GetInstance()->GetComponent<T>(shared_from_this());
		}

		void SetActive(const bool& state) { m_isActive = state; }

		bool IsActive()const { return m_isActive; }


		static Ref<Entity> Find(const std::string& name);

		static Ref<Entity> Create(const std::string& name);

		bool MatchesSignature(const Signature& signature);

	private:
		EntityID m_ID;
		Signature m_Signature;
		std::string m_Name;
		bool m_isActive;


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
				GE_CORE_WARN("Entity \"{0}\" was not found.", name);
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
		const std::vector<Ref<Entity>> GetEntities()const
		{
			std::vector<Ref<Entity>> ret;
			for (auto it : m_Entities) {
				ret.push_back(it.second);
			}
			return ret;
		}

	private:
		static std::queue<EntityID> s_AvailableIDs;
		std::unordered_map<std::string, Ref<Entity>> m_Entities;
		static bool m_init;

	private:
		static EntityID GetNextID()
		{
			EntityID nextID = s_AvailableIDs.front();
			EntityManager::s_AvailableIDs.pop();
			return nextID;
		}
	};

	using GameObject = gwcEngine::Ref<gwcEngine::Entity>;
}