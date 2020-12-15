#pragma once
#include "ECSTypes.h"
#include "Entity.h"
namespace gwcEngine
{
	class ECSManager;

	class ISystem
	{
		friend class SystemManager;

	public:
		virtual ~ISystem() = default;

		ISystem();
		

		virtual void OnUpdate(const float& dT)
		{

		}

		virtual void OnEntityRegistered(GameObject gameobject)
		{

		}

		virtual void OnEntityUnregistered(GameObject gameobject)
		{

		}

		virtual void RegisterRequiredComponents() = 0;
		virtual void InitSignature() = 0;

		virtual void ValidateEntity(const Ref<Entity>& entity)
		{
			Signature EntitySignature = entity->GetSignature();
			
			Signature result;
			result.reset();


			result = EntitySignature & m_Signature;

			
			auto it = std::find(m_EntityArray.begin(), m_EntityArray.end(), entity);

			if (result == m_Signature) {//if keep
				
				if (it == m_EntityArray.end()) {//and doesn't exist
					m_EntityArray.push_back(entity);
					OnEntityRegistered(entity);
					m_NumberEntities++;
				}
			}
			else {//if don't keep
				if (it != m_EntityArray.end()) {//and does exist
					m_EntityArray.erase(std::remove(m_EntityArray.begin(), m_EntityArray.end(), entity), m_EntityArray.end());
					OnEntityUnregistered(entity);
					m_NumberEntities--;
				}
			}
		}

		virtual void ValidateEntityArray(const std::unordered_map<std::string, Ref<Entity>>& entities)
		{
			for (auto& it : entities) {
				ValidateEntity(it.second);
			}
		}

		Signature GetSignature() const { return m_Signature; }

		void SetSignature(const Signature& signature) { m_Signature = signature; }

		void SetActive(bool state) { m_isActive = state; }
		bool IsActive() { return m_isActive; }


	protected:

		Signature m_Signature;
		std::vector<Ref<Entity>> m_EntityArray;
		uint32_t m_NumberEntities = 0;
		bool m_isActive = false;

		std::string m_name;
		SystemID m_ID;
		ECSManager* m_ECSManager;

	protected:
		void SetID(const SystemID& id) { m_ID = id; }

	};


	class SystemManager
	{
	public:
		void RegisterSystem(Ref<ISystem>& system)
		{
			m_SystemArray[m_NextID] = system;
			system->SetID(m_NextID);
			m_NextID++;
		}
		SystemID NumberOfSystems()const { return m_NextID; }

		void OnUpdate(const float& dT)
		{
			for (SystemID it = 0; it < NumberOfSystems(); it++) {
				m_SystemArray[it]->OnUpdate(dT);
			}
		}

		void OnEntityCompositionModified(const Ref<Entity>& entity)
		{
			for (SystemID it = 0; it < m_NextID; it++) {
				m_SystemArray[it]->ValidateEntity(entity);
			}
		}

		Ref<ISystem> FindSystem(const std::string& sysName)
		{
			for (auto it : m_SystemArray) {
				if (it->m_name == sysName) {
					return it;
				}
			}
		}

	private:
		std::array<Ref<ISystem>, MAX_SYSTEMS> m_SystemArray;
		SystemID m_NextID = 0;
	};
}