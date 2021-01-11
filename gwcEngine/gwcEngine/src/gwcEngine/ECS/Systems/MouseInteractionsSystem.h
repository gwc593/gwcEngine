#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Collider.h"

namespace gwcEngine
{

	class MouseInteractionsSystem : public ISystem
	{
	public:
		MouseInteractionsSystem(const std::string& name)
		{
			m_name = name;
			RegisterRequiredComponents();
			InitSignature();
		}

		virtual ~MouseInteractionsSystem() = default;

		virtual void RegisterRequiredComponents() override
		{
			m_ECSManager->RegisterCompType<gwcEngine::Collider>();
		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Collider>()] = true;
		}

		virtual void OnEarlyUpdate(const float& dT) override
		{

		}

		virtual void OnUpdate(const float& dT) override
		{

		}

		virtual void OnEntityRegistered(GameObject gameobject) override
		{

		}

		virtual void OnEntityUnregistered(GameObject gameobject) override
		{

		}
	};
}