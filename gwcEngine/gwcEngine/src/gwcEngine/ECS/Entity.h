#pragma once
#include "ECSTypes.h"
namespace gwcEngine
{

	
	class Entity
	{
	public:
		Entity();
		~Entity();

		Signature GetSignature() { return m_Signature; }
		void SetSignature(Signature signature) { m_Signature = signature; }

		void Destroy();

		template<typename T>
		void AddComponent();

		template<typename T>
		T& GetComponent();
	
	public:
		static void Init();
		static Entity& FindEntity(EntityID id);

	private:
		EntityID m_ID;
		Signature m_Signature;
		std::string m_Name;

		static std::queue<EntityID> m_AvailableIDs;
		static std::unordered_map<std::string, EntityID> m_Entities;
		static bool m_init;
	};

}