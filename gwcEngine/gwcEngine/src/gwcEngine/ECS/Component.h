#pragma once
#include"gepch.h"
#include "ECSTypes.h"
#include "Entity.h"

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
		T& GetComponent() { return *m_CompRef; }
	private:
		Ref<T> m_CompRef;
	};


	//Component Array interface (allow polymorphic array of pointers to component array base classes.
	class IComponentArray
	{
	public:
		virtual void RemoveEntity(const Ref<Entity>& entity) = 0;
	private:

	};

	//Component Array
	template<typename T>
	class ComponentArray: public IComponentArray
	{
	public:
		ComponentArray() = default;

		//method that returns a component assigned to an entity
		Ref<Component<T>> GetComponent(const Ref<Entity>& entity)
		{
			return m_CompArray[m_EntToArr[entity]];
		}

		virtual void RemoveEntity(const Ref<Entity>& entity) override
		{
			//keep array packed
			auto search = m_EntToArr.find(entity);
			if (search == m_EntToArr.end()) {
				GE_CORE_WARN("Entity: {0} does not have a {1}, it can therefore not be removed", entity->GetName(), typeid(T).name());
				return;
			}
			auto indexrmoved = m_EntToArr[entity];
			auto indexLast = m_Size - 1;
			auto lastEntity = m_ArrToEnt[indexLast];

			//set component of removed entity element equal to the last valid component in the array
			m_CompArray[indexrmoved] = m_CompArray[indexLast];
			
			//set the entity at the removed element equal to the last entity now that its data has been moved to the empty element
			m_ArrToEnt[indexrmoved] = lastEntity;
			
			//set the element associated to the moved entity equal to its new position
			m_EntToArr.erase(entity);
			m_EntToArr[lastEntity] = indexrmoved;
			
			m_ArrToEnt.erase(indexLast);

			m_Size--;
		}

		//Method to add Entity and component to array
		void AddEntity(const Ref<Entity>& ent, const Ref<Component<T>>& component)
		{
			auto search = m_EntToArr.find(ent);
			if (search != m_EntToArr.end()) {
				GE_CORE_WARN("Entity: {0} already has a {1}", ent->GetName(), typeid(T).name());
				return;
			}
			m_CompArray[m_Size] = component;
			m_EntToArr[ent] = m_Size;
			m_ArrToEnt[m_Size] = ent;
			m_Size++;
		}

	private:
		std::array<Ref<Component<T>>, MAX_ENTITIES> m_CompArray{};

		std::unordered_map<Ref<Entity>,uint32_t > m_EntToArr{};
		std::unordered_map<uint32_t, Ref<Entity>> m_ArrToEnt{};
		
		uint32_t m_Size = 0;

	};

	//Component Manager
	class ComponentManager
	{

	public:
		ComponentManager() = default;

		//static global behavior
		static ComponentID GetNextID() { return ComponentManager::s_NextID++; }

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
			auto search = ComponentManager::s_ComponentIDs.find(typeName);

			if (search == ComponentManager::s_ComponentIDs.end()) {
				auto newID = ComponentManager::GetNextID();
				ComponentManager::s_ComponentIDs.emplace(std::pair(typeName, newID));
				return newID;
			}

			return search->second;
		}

		template<typename T, typename... TArgs>
		T& AddComponent(Ref<Entity>entity, TArgs&&... mArgs) noexcept
		{
			//find component component array
			auto search = m_ArrayOfComponentArrays.find(typeid(T).name());

			//make new component
			Ref<Component<T>> _component{ new Component<T>(std::forward<TArgs>(mArgs)...) };
			
			//if component array does not exist within the array of component arrays, make it and add it.
			if (search == m_ArrayOfComponentArrays.end()){
				Ref<ComponentArray<T>> arrRef{ new ComponentArray<T>() };
				std::dynamic_pointer_cast<ComponentArray<T>>(arrRef)->AddEntity(entity, _component);
				m_ArrayOfComponentArrays.emplace(std::pair(typeid(T).name(), arrRef));
			}
			else {
				std::dynamic_pointer_cast<ComponentArray<T>>(search->second)->AddEntity(entity, _component);
			}

			Signature sig = entity->GetSignature();
			sig[_component->GetID()] = true;
			entity->SetSignature(sig);	

			return _component->GetComponent();
		}

		template<typename T>
		void RemoveComponent(Ref<Entity> entity) noexcept
		{
			auto search = m_ArrayOfComponentArrays.find(typeid(T).name());

			if (search == m_ArrayOfComponentArrays.end()) {
				GE_CORE_WARN("{0} does not contain component: {1}", entity->GetName(), typeid(T).name());
			}

			std::dynamic_pointer_cast<ComponentArray<T>>(search->second)->RemoveEntity(entity);
			Signature sig = entity->GetSignature();
			sig[ComponentManager::FindID(typeid(T).name())] = false;
			entity->SetSignature(sig);
		}

		template<typename T>
		T& GetComponent(const Ref<Entity>& entity) noexcept
		{
			auto compArr = m_ArrayOfComponentArrays.find(typeid(T).name());

			if (compArr == m_ArrayOfComponentArrays.end()) {
				GE_CORE_WARN("{0} does not have component {1}", entity->GetName(), typeid(T).name());
				return *(T*)nullptr;
			}

			auto comptContainer = (std::dynamic_pointer_cast<ComponentArray<T>>(compArr->second)->GetComponent(entity));

			return comptContainer->GetComponent();
		}
	protected:


	private:
		//list of component types against their IDs
		static std::unordered_map<std::string, ComponentID> s_ComponentIDs;

		//next Id for a component type
		static ComponentID s_NextID;

		//Array of component Arrays
		std::unordered_map<std::string,Ref<IComponentArray>> m_ArrayOfComponentArrays;
		


	};


}