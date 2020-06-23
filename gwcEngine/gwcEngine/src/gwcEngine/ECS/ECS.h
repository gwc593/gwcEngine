#pragma once
#include"gwcEngine/ECS/Entity.h"
#include"gwcEngine/ECS/Component.h"
#include"gwcEngine/ECS/System.h"

namespace gwcEngine 
{
	class ECSGlobalManager
	{
	public:		


		~ECSGlobalManager()
		{
			delete s_instance;
		};
	
		
		static ECSGlobalManager* GetInstance()
		{
			if (s_instance == nullptr) 
			{
				s_instance = new ECSGlobalManager;
			}
			return s_instance; 
		}
	private:

		static ECSGlobalManager* s_instance;

		ECSGlobalManager()
		{
			EntityManager::Init();
		}
	};

	class ECSLayerManager
	{
	public:
		ECSLayerManager() = default;
#pragma region Entity Manager Interface
		Entity& FindEntity(const std::string& name)
		{
			return m_EntityManager.FindEntity(name);
		}

		void DestroyEntity(Entity& entity)
		{
			m_EntityManager.DestroyEntity(entity);
		}

		Ref<Entity> CreateEntity(const std::string& name)
		{
			return m_EntityManager.CreateEntity(name);
		}
#pragma endregion


#pragma region Component Manager Interface
		template<typename T>
		ComponentID FindID()
		{
			return ComponentManager::FindID<T>();
		}

		template<typename T>
		ComponentID RegisterCompType()
		{
			return ComponentManager::RegisterCompType<T>();
		}

		template<typename T, typename... TArgs>
		T& AddComponent(Ref<Entity>entity, TArgs&&... mArgs) noexcept
		{
			return m_ComponentManager.AddComponent<T>(entity, std::forward<TArgs>(mArgs)...);
		}

		template<typename T>
		void RemoveComponent(Ref<Entity> entity) noexcept
		{
			m_ComponentManager.RemoveComponent<T>(entity);
		}

		template<typename T>
		T& GetComponent(const Ref<Entity>& entity)
		{
			return m_ComponentManager.GetComponent<T>(entity);
		}
#pragma endregion

	private:
		gwcEngine::EntityManager m_EntityManager;
		gwcEngine::ComponentManager m_ComponentManager;
		gwcEngine::SystemManager m_SystemManager;
	};
	
}