#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Cameras/Camera.h"


namespace gwcEngine 
{
	class CameraSystem : public ISystem
	{
	public:
		CameraSystem(const std::string& name)
		{
			m_name = name;
			RegisterRequiredComponents();
			InitSignature();
		}

		virtual void RegisterRequiredComponents() override
		{
			m_ECSManager->RegisterCompType<gwcEngine::Camera>();
			m_ECSManager->RegisterCompType<gwcEngine::Transform>();
			m_ECSManager->RegisterCompType<gwcEngine::RenderLayer>();
		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Camera>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Transform>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::RenderLayer>()] = true;
		}

		virtual void OnEntityRegistered(GameObject gameobject) override
		{
			//get components
			auto tr = gameobject->GetComponent<Transform>();
			auto cm = *gameobject->GetComponent<Camera>();

			//make callback to recalculate viewmatrix on a transfrom change.
			auto cblmb = [cm](const Transform& trans) {cm->CalculateViewMatrix(); return PROPAGATE_EVENT; };
			Ref<EventCallback<const Transform&>> CB {new EventCallback<const Transform&>(cblmb)};

			gameobject->AddComponent<Ref<EventCallback<const Transform&>>>(CB);
			
			//set the cameras transform referenct
			cm->SetTransformRef(tr);
			
			//subscribe the camera to update its viewMatrix 
			tr->OnChangeSubscribe(CB);
		}

		const std::vector<Ref<Entity>>& GetEntities()const { return m_GameObjectArray; }

		virtual void OnEarlyUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			for (auto gameObject : m_GameObjectArray) {
				gwcEngine::RenderCommand::SetClearColour((*gameObject->GetComponent<Camera>())->GetClearColour());
				(*gameObject->GetComponent<Camera>())->GetFrameBuffer()->Clear();
			}
		}
	};
 

}