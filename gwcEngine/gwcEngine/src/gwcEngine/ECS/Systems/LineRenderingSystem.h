#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Renderable/Mesh.h"
#include "gwcEngine/Components/Renderable/LineRenderer.h"
#include "gwcEngine/Components/Physics/Ray.h"

#include "gwcEngine/Components/Cameras/Camera.h"
#include "gwcEngine/Renderer/Renderer.h"
#include <set>
namespace gwcEngine
{
	class LineRenderingSystem : public ISystem
	{
	public:

		LineRenderingSystem(const std::string name)
		{
			m_name = name;
			RegisterRequiredComponents();
			InitSignature();
			auto ECS = ECSManager::GetInstance();

			m_ECS_UpdatedCallback = CreateRef< EventCallback<const GameObject&>>([this](const GameObject& go) {return this->ECS_UpdateCallback(go); });
			auto& ecsEvent = ECS->GetOnECSUpdated();
			ecsEvent.subscribe(m_ECS_UpdatedCallback);


			//todo, base camera class should hold a register of all entities which contain a camera, that way multiple systems dont need to!
			m_CameraObjSig[ECS->FindComponentID<Camera>()] = true;
			m_CameraObjSig[ECS->FindComponentID<Transform>()] = true;
			m_CameraObjSig[ECS->FindComponentID<RenderLayer>()] = true;

			m_LineShader = Shader::Create("assets/Shaders/LineShader.glsl");
			
		}

		virtual void RegisterRequiredComponents() override
		{
			m_ECSManager->RegisterCompType<gwcEngine::Transform>();
			m_ECSManager->RegisterCompType<gwcEngine::Mesh>();
			m_ECSManager->RegisterCompType<gwcEngine::LineRenderer>();
			m_ECSManager->RegisterCompType<gwcEngine::Ray>();
			
			m_ECSManager->RegisterCompType<gwcEngine::Camera>();
			m_ECSManager->RegisterCompType<gwcEngine::RenderLayer>();

		}

		virtual void InitSignature() override
		{
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Transform>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::Mesh>()] = true;
			m_Signature[m_ECSManager->FindComponentID<gwcEngine::LineRenderer>()] = true;
			//m_Signature[m_ECSManager->FindComponentID<gwcEngine::Ray>()] = true;

		}


		virtual void OnUpdate(const float& dT)
		{
			PROFILE_FUNCTION();
			Ref<Camera> currentCamera;

			for (auto camera : m_Cameras) {
				if (camera->IsActive()) {

					currentCamera = camera->GetComponent<Camera>();

					(*currentCamera)->GetFrameBuffer()->Bind();
					gwcEngine::Renderer::SetActiveCamera((*currentCamera));

					for (auto gameObject : m_GameObjectArray) {
						if (gameObject->IsActive()) {
							if (((gameObject->GetComponent<LineRenderer>()->GetActiveLayers()) & (camera->GetComponent<RenderLayer>()->GetActiveLayers())).any()) {//if object is on a camera's layer
								auto mesh = gameObject->GetComponent<gwcEngine::Mesh>();
								auto transform = gameObject->GetComponent<gwcEngine::Transform>();
								auto material = gameObject->GetComponent<gwcEngine::Material>();
								
								glm::vec2 vpData{ 1.0f / ((float)(*currentCamera)->GetWidth()),1.0f / ((float)(*currentCamera)->GetHeight()) };

								m_LineShader->UploadUniformVec2("u_viewportInvSize", vpData);
								m_LineShader->UploadUniformVec4("u_color", { 1.0, 0, 0,1.0 });

								Renderer::Submit(mesh->GetVertexArray(), m_LineShader, transform->GetTransformMatrix(), RendType::lines);
							}
						}
					}

					(*currentCamera)->GetFrameBuffer()->Unbind();
				}
			}
		}

		bool ECS_UpdateCallback(const GameObject& gameObject)
		{
			auto found = m_Cameras.find(gameObject);

			//if keep
			if (gameObject->MatchesSignature(m_CameraObjSig)) {
				if (found == m_Cameras.end())
					m_Cameras.insert(gameObject);
			}
			else {
				if (found != m_Cameras.end())
					m_Cameras.erase(found);
			}

			return PROPAGATE_EVENT;
		}

	private:
		Signature m_CameraObjSig;
		std::set<GameObject> m_Cameras;
		Ref<EventCallback<const GameObject&>> m_ECS_UpdatedCallback;
		Ref<Shader> m_LineShader;
	};
}