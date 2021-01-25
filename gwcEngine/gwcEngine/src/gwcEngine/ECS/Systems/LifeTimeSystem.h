#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/LifeTime.h"

namespace gwcEngine
{

	class LifeTimeSystem : public ISystem
	{
	public:
		LifeTimeSystem(const std::string name)
		{
			m_name = name;
			RegisterRequiredComponents();
			InitSignature();
		}

		virtual void RegisterRequiredComponents() override
		{
			m_ECSManager->RegisterCompType<gwcEngine::LifeTime>();
		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::LifeTime>()] = true;
		}

		virtual void OnUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			for (auto GO : m_GameObjectArray) {
				if (GO->GetComponent<LifeTime>()->GetLifeRemaining() <= 0) {
					Entity::Destroy(GO);
					break;
				}
			}
		}

	protected:
		bool m_AllProcessed = false;
	};
}
