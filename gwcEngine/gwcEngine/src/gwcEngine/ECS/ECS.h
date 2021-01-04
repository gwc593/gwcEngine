#pragma once
#include"gwcEngine/ECS/Entity.h"
#include"gwcEngine/ECS/Component.h"
#include"gwcEngine/ECS/System.h"

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

#pragma region Entity Manager Interface
		Ref<Entity> FindEntity(const std::string& name)
		{
			return m_EntityManager.FindEntity(name);
		}

		void DestroyEntity(Ref<Entity>& entity)
		{
			m_ComponentManager.RemoveAllComponents(entity);
			m_SystemManager.OnEntityCompositionModified(entity);
			m_EntityManager.DestroyEntity(entity);
		}

		Ref<Entity> CreateEntity(const std::string& name = "unNamed")
		{
			auto ret = m_EntityManager.CreateEntity(name);
			m_SystemManager.OnEntityCompositionModified(ret);
			return ret;
		}

		std::vector<Ref<Entity>> FindEntitiesOfSignature(const Signature& signature)
		{
			std::vector<Ref<Entity>> ret;
			Signature result;
			result.reset();

			for (auto ent : m_EntityManager.GetEntities()) {
				result = ent->GetSignature() & signature;
				if (result == signature) {
					ret.push_back(ent);
				}
				result.reset();
			}

			return ret;
		}
#pragma endregion


#pragma region Component Manager Interface
		template<typename T>
		ComponentID FindComponentID()
		{
			return ComponentManager::FindID<T>();
		}

		template<typename T>
		ComponentID RegisterCompType()
		{
			return ComponentManager::RegisterCompType<T>();
		}

		template<typename T, typename... TArgs>
		Ref<T> AddComponent(Ref<Entity>entity, TArgs&&... mArgs) noexcept
		{
			Ref<T> ret = m_ComponentManager.AddComponent<T>(entity, std::forward<TArgs>(mArgs)...);
			m_SystemManager.OnEntityCompositionModified(entity);
			return ret;
		}

		template<typename T>
		void RemoveComponent(Ref<Entity> entity) noexcept
		{
			m_ComponentManager.RemoveComponent<T>(entity);
			m_SystemManager.OnEntityCompositionModified(entity);
		}

		template<typename T>
		Ref<T> GetComponent(const Ref<Entity>& entity)
		{
			return m_ComponentManager.GetComponent<T>(entity);
		}

		template<typename T>
		ComponentID FindID()
		{
			return ComponentManager::FindID<T>();
		}

		const Event<const GameObject&>& GetOnECSUpdated() { return m_ComponentManager.GetOnECSUpdateEvent(); }

#pragma endregion


#pragma region System Manager Interface
		void RegisterSystem(Ref<ISystem>& system)
		{
			m_SystemManager.RegisterSystem(system);
		}

		void OnEarlyUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			m_SystemManager.OnEarlyUpdate(dT);
		}

		void OnUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			m_SystemManager.OnUpdate(dT);
		}

		Ref<ISystem> FindSystem(const std::string& sysName)
		{
			return m_SystemManager.FindSystem(sysName);
		}

#pragma endregion

	private:

		static ECSManager* s_instance;

		ECSManager()
		{
			EntityManager::Init();
		}

		gwcEngine::EntityManager m_EntityManager;
		gwcEngine::ComponentManager m_ComponentManager;
		gwcEngine::SystemManager m_SystemManager;


	};
}