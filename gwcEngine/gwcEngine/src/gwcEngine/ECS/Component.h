#pragma once
#include"gepch.h"
#include "ECSTypes.h"

namespace gwcEngine
{


	//Component Interface and base class to allow polymorphic vector of component array templates.
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		ComponentID GetID() { return m_ID; }
	protected:
		ComponentID m_ID;
	};



	//Template Component Class
	template<typename T, typename... TArgs>
	class Component : public IComponent
	{
	public:
		Component(TArgs&&... mArgs)
			:
			m_CompRef(new T(std::forward<TArgs>(mArgs)...))
		{
			m_ID = ComponentManager::RegisterCompType(typeid(T).name());
		}

		virtual ~Component() = default;

		Ref<T> m_CompRef;
	};

	//Component Manager
	class ComponentManager
	{
	public:
		static ComponentID GetNextID() { return s_NextID++; }
		static ComponentID FindID(const std::string& typeName)
		{
			auto search = s_ComponentIDs.find(typeName);

			if (search == s_ComponentIDs.end()) {
				return NullComponentID;
			}
			
			return search->second;
		}

		static ComponentID RegisterCompType(const std::string& typeName)
		{
			auto search = s_ComponentIDs.find(typeName);

			if (search == s_ComponentIDs.end()) {
				auto newID = GetNextID();
				s_ComponentIDs.emplace(std::pair(typeName, newID));
				return newID;
			}

				return search->second;
		}

	private:
		//static enforced singleton
		ComponentManager();

		//next Id for a component type
		static ComponentID s_NextID;
		
		//list of component types against their IDs
		static std::unordered_map<std::string, ComponentID> s_ComponentIDs;

	};



	//Component Array interface (allow polymorphic array of pointers to component array base classes.
	class IComponentArray
	{
	public:
		virtual void RemoveEntity(EntityID entity) = 0;
	private:

	};

	//Component Array
	template<typename T>
	class ComponentArray: public IComponentArray
	{
	public:
		ComponentArray() = default;

		//method that returns a component assigned to an entity
		T& GetComponent(EntityID entity) { return m_CompArray[m_ArrayToEntityID[entity]]; }

		virtual void RemoveEntity() override
		{
			
		}

		//Method to add Entity and component to array
		void AddEntity(EntityID entity, Ref<T> component)
		{

		}

	private:
		std::array<T, MAX_ENTITIES> m_CompArray{};

		std::unordered_map<EntityID, uint32_t> m_ArrayToEntityID{};
		uint32_t m_Size = 0;

	};


}