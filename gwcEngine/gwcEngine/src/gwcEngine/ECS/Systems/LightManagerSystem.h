#pragma once
#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Renderab"
#include "gwcEngine/Renderer/Material.h"

#include<set>

namespace gwcEngine
{
	class LightManagerSystem : public ISystem
	{
	public:
		LightManagerSystem(const std::string name)
		{
			m_name = name;
			RegisterRequiredComponents();
			InitSignature();
		}

		virtual void RegisterRequiredComponents() override
		{
			m_ECSManager->RegisterCompType<gwcEngine::Transform>();

		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Transform>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Mesh>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Material>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::MeshRenderer>()] = true;
		}
	private:

	}
}
