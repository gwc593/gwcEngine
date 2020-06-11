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
			return m_ComponentBitset[GetComponentID<T>];
		}

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = c;
			m_ComponentBitset[GetComponentTypeID<T>()] = true;

			c->Init();
			return *c;
		}

		template <typename T> T& GetComponent()
		{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

	private:
		bool m_Active;

		std::vector<std::unique_ptr<Component>> m_Components;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitset;
	};


	class ECSManager
	{
	public:

		void OnUpdate()
		{
			for (auto& ent : entities) ent->OnUpdate();
		}

		void Draw()
		{
			for (auto& ent : entities) ent->Draw();
		}

		bool OnEvent(const Event& e)
		{
			for (auto& ent : entities) return ent->OnEvent(e);
		}

		void Refresh()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
										  [](const std::unique_ptr<Entity>& mEntity)
										  {
											  return !mEntity->IsActive();
										  }), std::end(entities));
		}

		Entity& AddEntity()
		{
			Entity* e = new Entity();
			std::unique_ptr<Entity> uPtr{ e };
			entities.emplace_back(std::move(uPtr));

			return *e;
		}

	private:
		std::vector<std::unique_ptr<Entity>> entities;


	};

}