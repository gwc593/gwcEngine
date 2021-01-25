#pragma once
#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Renderable/Light.h"
#include "gwcEngine/Renderer/Shader/Shader.h"

#define MAX_LIGHTS 20
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
			m_ECSManager->RegisterCompType<Transform>();
			m_ECSManager->RegisterCompType<Light>();
		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<Transform>()] = true;
			m_Signature[m_ECSManager->FindComponentID<Light>()] = true;
		}


		virtual void OnLateUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			UploadLightData();
		}

		virtual void OnEntityRegistered(GameObject gameobject)
		{
			if (m_GameObjectArray.size() >= MAX_LIGHTS) {
				GE_WARN("Maximum number of lights exceeded, Light object removed from {0}", gameobject->GetName());
				gameobject->RemoveComponent<Light>(); 
			}
		}

	protected:
		void UploadLightData()
		{
			for (auto shaderPtr : Shader::GetShaders()) {
				auto shader = shaderPtr.lock();
				shader->UploadUniformInt("u_NumLights", (int)m_GameObjectArray.size());
				for (size_t i = 0; (i < MAX_LIGHTS) && (i < m_GameObjectArray.size()); ++i) {
					auto props = m_GameObjectArray[i]->GetComponent<Light>()->GetProperties();
					auto trans = m_GameObjectArray[i]->GetComponent<Transform>();
					shader->UploadUniformBool(std::string("u_Lights[") + std::to_string(i) + std::string("].isEnabled"), props.isEnabled?1:0);
					shader->UploadUniformBool(std::string("u_Lights[") + std::to_string(i) + std::string("].isLocal"), props.isLocal);
					shader->UploadUniformBool(std::string("u_Lights[") + std::to_string(i) + std::string("].isSpot"), props.isSpot);
					shader->UploadUniformVec3(std::string("u_Lights[") + std::to_string(i) + std::string("].ambient"), props.ambient);
					shader->UploadUniformVec3(std::string("u_Lights[") + std::to_string(i) + std::string("].colour"), props.colour);
					shader->UploadUniformVec3(std::string("u_Lights[") + std::to_string(i) + std::string("].position"), trans->GetPosition(Space::world));
					shader->UploadUniformVec3(std::string("u_Lights[") + std::to_string(i) + std::string("].halfVector"), props.halfVector);
					shader->UploadUniformVec3(std::string("u_Lights[") + std::to_string(i) + std::string("].coneDirection"), -trans->Up());
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].spotCutoff"), props.spotCutoff);
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].spotExponent"), props.spotExponent);
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].constantAttenuation"), props.constantAttenuation);
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].linearAttenuation"), props.linearAttenuation);
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].quadraticAttenuation"), props.quadraticAttenuation);
					shader->UploadUniformFloat(std::string("u_Lights[") + std::to_string(i) + std::string("].strength"), props.strength);
				}
			}
		}
	};
}
