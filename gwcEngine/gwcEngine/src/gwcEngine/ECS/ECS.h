#pragma once
#include "gepch.h"
#include"gwcEngine/Events/Event.h"


namespace gwcEngine
{
	class Component;
	class Entity;

	using ComponentID = std::size_t;

	inline ComponentID GetComponentTypeID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}

	template<typename T> inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID typeID = GetComponentTypeID();
		return typeID;
	}

	constexpr::size_t maxComponents = 32;

	//bitwise signature of the components on an entity.
	using ComponentBitSet = std::bitset<maxComponents>;

	//array of component pointer on an entity..
	using ComponentArray = std::array<Component*, maxComponents>;

	class Component
	{
	public:
		Entity* entity;

		virtual ~Component() {};

		virtual void Init() {};

		virtual void OnUpdate() {};

		virtual void Draw() {};

		virtual bool OnEvent(const Event& e) { return false; }

	};

	class Entity
	{
	public:
		Entity() = default;
		void OnUpdate()
		{
			for (auto& c : m_Components) c->OnUpdate();
			for (auto& c : m_Components) c->Draw();
		}

		void Draw() {}

		bool IsActive() const { return m_Active; }

		void Destroy() { m_Active = false; }

		bool OnEvent(const Event& e) { return false; }

		template <typename T> bool HasComponent()
		{
			return m_ComponentBitset[GetComponentID<T>()];
		}

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... mArgs)
		{
			//Todo - Validation that T is indeed a subclass of Component base.
			T* _comp(new T(std::forward<TArgs>(mArgs)...));
			
			_comp->entity = this;
			std::shared_ptr<Component> uPtr{ _comp };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = _comp;
			m_ComponentBitset[GetComponentTypeID<T>()] = true;

			_comp->Init();
			return *_comp;
		}



		template <typename T> T& GetComponent()
		{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			if (ptr == nullptr)
				GE_CORE_ERROR("{0} {1}", typeid(T).name(), "doest exist on this component");
			return *static_cast<T*>(ptr);
		}

		
		Entity::Entity(const Entity& other)
		{
			GE_CORE_ERROR("Copying entities outside of the manager is forbidden,null object returned");
			GE_CORE_WARN("Please Copy by reference or use 'duplicate' method within the ECS manager instead. null returned..");
		}
	private:
		bool m_Active = true;
		
	private:
		
		std::vector<std::shared_ptr<Component>> m_Components;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitset;

	};
	class ECSManager
	{
	public:
		ECSManager() = default;

		void OnUpdate()
		{
			for (auto& ent : m_Entities) ent.second->OnUpdate();
		}

		void Draw()
		{
			for (auto& ent : m_Entities) ent.second->Draw();
		}

		bool OnEvent(const Event& e)
		{
			for (auto& ent : m_Entities) return ent.second->OnEvent(e);
		}

		void Refresh()
		{
			m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities),
										  [](const std::pair<std::string, std::shared_ptr<Entity>>& mEntity)
										  {
											  return !mEntity.second->IsActive();
										  }), std::end(m_Entities));
		}

		Entity& AddEntity(const std::string& name)
		{
			//todo Key pair with string name so you can do FindEntity(const std::string& name){return entity....}
			Entity* e = new Entity();
			std::shared_ptr<Entity> uPtr{ e };

			std::pair<std::string, std::shared_ptr<Entity>> element;
			element.first = name;
			//element.second = std::move(uPtr);

			m_Entities.emplace_back(element);
			m_Entities.back().second = std::move(uPtr);
			return *e;
		}

		Entity& FindEntity(const std::string& name) const
		{
			for (auto& ent : m_Entities) {
				if (ent.first == name) {
					return *ent.second;
				}
			}
			return *(Entity*)nullptr;
		}


	private:
		std::vector<std::pair<std::string, std::shared_ptr<Entity>>> m_Entities;


	};

}