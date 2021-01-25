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
		ComponentID m_ID = MAX_COMPONENTS;
	};



	//Template Component Class
	template<typename T, typename... TArgs>
	class Component : public IComponent
	{
	public:
		Component(TArgs... mArgs)
			:
			m_CompRef(new T(std::forward<TArgs>(mArgs)...))
		{
			m_ID = ComponentManager::RegisterCompType<T>();
		}

		virtual ~Component() = default;
		Ref<T> GetComponent() { return m_CompRef; }
	private:
		Ref<T> m_CompRef;
	};


	//Component Array interface (allow polymorphic array of pointers to component array base classes.
	class IComponentArray
	{
	public:
		virtual void RemoveEntity(const Ref<Entity>& entity, bool warn = true) = 0;
	private:

	};

	//Component Array
	template<typename T>
	class ComponentArray: public IComponentArray
	{
	public:
		ComponentArray() = default;

		//method that returns a component assigned to an entity
		Ref<Component<T>>& GetComponent(const Ref<Entity>& entity)
		{
			return m_CompArray[m_EntToArr[entity]];
		}

		virtual void RemoveEntity(const Ref<Entity>& entity, bool warn = true) override
		{
			//keep array packed
			auto search = m_EntToArr.find(entity);
			if (search == m_EntToArr.end()&&warn) {
				GE_CORE_WARN("Entity: {0} does not have a {1}, it can therefore not be removed", entity->GetName(), typeid(T).name());
				return;
			}

			if (search == m_EntToArr.end() && !warn) {
				return;
			}
			auto indexrmoved = m_EntToArr[entity];
			auto indexLast = m_Size - 1;
			auto lastEntity = m_ArrToEnt[indexLast];

			//TODO need to call destructor of double pointer components like panels and cameras used for polymorphism
			auto x = m_CompArray[indexrmoved]->GetComponent();
			x->~T();

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



	template<typename T>
	class ComponentArray<Ref<T>> : public IComponentArray
	{
	public:
		ComponentArray() = default;

		//method that returns a component assigned to an entity
		Ref<Component<Ref<T>>>& GetComponent(const Ref<Entity>& entity)
		{
			return m_CompArray[m_EntToArr[entity]];
		}

		virtual void RemoveEntity(const Ref<Entity>& entity, bool warn = true) override
		{
			//keep array packed
			auto search = m_EntToArr.find(entity);
			if (search == m_EntToArr.end() && warn) {
				GE_CORE_WARN("Entity: {0} does not have a {1}, it can therefore not be removed", entity->GetName(), typeid(T).name());
				return;
			}

			if (search == m_EntToArr.end() && !warn) {
				return;
			}
			auto indexrmoved = m_EntToArr[entity];
			auto indexLast = m_Size - 1;
			auto lastEntity = m_ArrToEnt[indexLast];

			//TODO need to call destructor of double pointer components like panels and cameras used for polymorphism
			//auto x = m_CompArray[indexrmoved]->GetComponent().reset();
			//m_CompArray[indexrmoved]->GetComponent().reset();
			//m_CompArray[indexrmoved].reset();
			////(*x)->~T();


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
		void AddEntity(const Ref<Entity>& ent, const Ref<Component<Ref<T>>>& component)
		{
			auto search = m_EntToArr.find(ent);
			if (search != m_EntToArr.end()) {
				GE_CORE_WARN("Entity: {0} already has a {1}", ent->GetName(), typeid(Ref<T>).name());
				return;
			}
			m_CompArray[m_Size] = component;
			m_EntToArr[ent] = m_Size;
			m_ArrToEnt[m_Size] = ent;
			m_Size++;
		}

	private:
		std::array<Ref<Component<Ref<T>>>, MAX_ENTITIES> m_CompArray{};

		std::unordered_map<Ref<Entity>, uint32_t > m_EntToArr{};
		std::unordered_map<uint32_t, Ref<Entity>> m_ArrToEnt{};

		uint32_t m_Size = 0;

	};


	//Component Manager
	class ComponentManager
	{

	public:
		ComponentManager() = default;

		//static global behavior


		template<typename T>
		static ComponentID FindID()
		{
			auto search = s_ComponentIDs.find(typeid(T).name());

			if (search == s_ComponentIDs.end()) {
				GE_CORE_WARN("{0}: is not a type managed or registered within the ECS manager, are you sure its being used?", typeid(T).name());
				return NullComponentID;
			}

			return search->second;
		}

		static ComponentID FindID(const std::string& name)
		{
			auto search = s_ComponentIDs.find(name);

			if (search == s_ComponentIDs.end()) {
				GE_CORE_WARN("{0}: is not a type managed or registered within the ECS manager, are you sure its being used?", name);
				return NullComponentID;
			}

			return search->second;
		}

		template<typename T>
		static ComponentID RegisterCompType()
		{
			auto search = ComponentManager::s_ComponentIDs.find(typeid(T).name());

			if (search == ComponentManager::s_ComponentIDs.end()) {
				auto newID = ComponentManager::GetNextID();
				ComponentManager::s_ComponentIDs.emplace(std::pair(typeid(T).name(), newID));
				return newID;
			}

			return search->second;
		}
		
		template<typename T, typename... TArgs>
		Ref<T> AddComponent(Ref<Entity>entity, TArgs&&... mArgs) noexcept
		{
			//find component component array
			auto search = m_ArrayOfComponentArrays.find(typeid(T).name());

			//TODO - I know, this is hideous type punning, but it works... Is there a cleaner way?
			Ref<Component<T>> _component( (Component<T>*) &(*new Component<T, TArgs...>(std::forward<TArgs>(mArgs)...)));


			//if component array does not exist within the array of component arrays, make it and add it.
			if (search == m_ArrayOfComponentArrays.end()){
				auto arrRef{ new ComponentArray<T>() };
				arrRef->AddEntity(entity, _component);
				m_ArrayOfComponentArrays.emplace(std::pair(typeid(T).name(), arrRef));
			}
			else {
				std::dynamic_pointer_cast<ComponentArray<T>>(search->second)->AddEntity(entity, _component);
			}

			Signature sig = entity->GetSignature();
			sig[_component->GetID()] = true;
			entity->SetSignature(sig);	

			m_OnECSUpdate.raiseEvent(entity);
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
			sig[ComponentManager::FindID<T>()] = false;
			entity->SetSignature(sig);

			m_OnECSUpdate.raiseEvent(entity);
		}

		void RemoveAllComponents(Ref<Entity> entity) noexcept
		{
			for (auto arr : m_ArrayOfComponentArrays) {
				(arr.second)->RemoveEntity(entity,false);
				Signature sig = entity->GetSignature();
				sig[ComponentManager::FindID(arr.first)] = false;
				entity->SetSignature(sig);
			}
	
			m_OnECSUpdate.raiseEvent(entity);
		}

		template<typename T>
		Ref<T> GetComponent(const Ref<Entity>& entity) noexcept
		{
			auto compArr = m_ArrayOfComponentArrays.find(typeid(T).name());

			if (compArr == m_ArrayOfComponentArrays.end()) {
				GE_CORE_WARN("Entity \"{0}\" does not have component \" {1} \"", entity->GetName(), typeid(T).name());
				return nullptr;
			}

			auto comptContainer = (std::dynamic_pointer_cast<ComponentArray<T>>(compArr->second))->GetComponent(entity);

			return comptContainer->GetComponent();
		}


		const Event<const GameObject&>& GetOnECSUpdateEvent()const { return m_OnECSUpdate; }



	private:
		static ComponentID GetNextID() { return ComponentManager::s_NextID++; }

		//list of component types against their IDs
		static std::unordered_map<std::string, ComponentID> s_ComponentIDs;

		//next Id for a component type
		static ComponentID s_NextID;

		//Array of component Arrays
		std::unordered_map<std::string,Ref<IComponentArray>> m_ArrayOfComponentArrays;
		
		Event<const GameObject&> m_OnECSUpdate;

	};


}