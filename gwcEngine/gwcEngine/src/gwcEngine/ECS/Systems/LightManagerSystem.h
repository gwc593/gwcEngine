#pragma once
#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Renderable/Light.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Renderer/Shader/UniformBuffer.h"

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

			if(!s_LightUniformBuffer)
				s_LightUniformBuffer = UniformBuffer::Create("LightBlock");

			UniformBufferStruct LightStruct;
			LightStruct.AddElement("isEnabled", UniformBufferTypes::Bool);
			LightStruct.AddElement("isLocal", UniformBufferTypes::Bool);
			LightStruct.AddElement("isSpot", UniformBufferTypes::Bool);
			LightStruct.AddElement("ambient", UniformBufferTypes::Vec4);
			LightStruct.AddElement("colour", UniformBufferTypes::Vec4);
			LightStruct.AddElement("position", UniformBufferTypes::Vec4);
			LightStruct.AddElement("halfVector", UniformBufferTypes::Vec4);
			LightStruct.AddElement("coneDirection", UniformBufferTypes::Vec4);
			LightStruct.AddElement("spotCutoff", UniformBufferTypes::Float);
			LightStruct.AddElement("spotExponent", UniformBufferTypes::Float);
			LightStruct.AddElement("constantAttenuation", UniformBufferTypes::Float);
			LightStruct.AddElement("linearAttenuation", UniformBufferTypes::Float);
			LightStruct.AddElement("quadraticAttenuation", UniformBufferTypes::Float);
			LightStruct.AddElement("strength", UniformBufferTypes::Float);

			s_LightUniformBuffer->AddElement("numLights", UniformBufferTypes::Int);
			s_LightUniformBuffer->AddStructure("lights", LightStruct, 20);
		}

		static const UniformBuffer* GetLightingUBO() { return s_LightUniformBuffer; }

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
			int numLights = (int)m_GameObjectArray.size();
			s_LightUniformBuffer->Set("numLights", &numLights,sizeof(int));
			for (size_t i = 0; (i < MAX_LIGHTS) && (i < m_GameObjectArray.size()); ++i) {
				auto props = m_GameObjectArray[i]->GetComponent<Light>()->GetProperties();
				auto trans = m_GameObjectArray[i]->GetComponent<Transform>();

				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].isEnabled", &props.isEnabled, sizeof(bool));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].isLocal", &props.isLocal, sizeof(bool));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].isSpot", &props.isSpot, sizeof(bool));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].ambient", &props.ambient, sizeof(glm::vec4));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].colour", &props.colour, sizeof(glm::vec4));

				auto pos = glm::vec4(trans->GetPosition(Space::world), 1.0);
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].position", &pos,sizeof(glm::vec4));

				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].halfVector", &props.halfVector, sizeof(glm::vec4));
				auto cd = glm::vec4(-trans->Up(), 1.0);

				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].coneDirection", &cd, sizeof(glm::vec4));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].spotCutoff", &props.spotCutoff, sizeof(float));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].spotExponent", &props.spotExponent, sizeof(float));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].constantAttenuation", &props.constantAttenuation, sizeof(float));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].linearAttenuation", &props.linearAttenuation, sizeof(float));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].quadraticAttenuation", &props.quadraticAttenuation, sizeof(float));
				s_LightUniformBuffer->Set("lights[" + std::to_string(i) + "].strength", &props.strength, sizeof(float));
			}

			s_LightUniformBuffer->SyncData();

			
		}

		static UniformBuffer* s_LightUniformBuffer;
	};
}
