#pragma once
#include"gwcEngine/ECS/System.h"
#include "gwcEngine/ECS/ECS.h"
#include "gwcEngine/ECS/Components/Mesh.h"
#include "gwcEngine/ECS/Components/Transform.h"
#include "gwcEngine/Renderer/Material.h"
#include "gwcEngine/Renderer/Renderer.h"
namespace gwcEngine 
{
	class RendererECS : public ISystem
	{
	public:
		RendererECS(const std::string& name, ECSLayerManager& manager)
			:m_ECSManager(manager)
		{
			m_name = name;
		}

		virtual ~RendererECS() = default;

		virtual void OnUpdate(const float& dT) override
		{
			for (auto& it = m_EntityArray.begin(); it != m_EntityArray.end(); it++) {
				
				auto mesh = m_ECSManager.GetComponent<gwcEngine::Mesh>(*it);
				auto Transform = m_ECSManager.GetComponent<gwcEngine::Transform>(*it);
				auto Material = m_ECSManager.GetComponent<gwcEngine::Material>(*it);

				
				Renderer::Submit(mesh.GetVertexArray(), Material);

			}
		}


	private:
		ECSLayerManager& m_ECSManager;
	};

}