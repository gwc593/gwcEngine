#include"gepch.h"
#include"Camera.h"
#include"gwcEngine/Renderer/Renderer.h"

namespace gwcEngine 
{
	void CameraBase::CalculateViewMatrix()
	{
	
		glm::mat4 transform;
		if (m_Transform != nullptr)
			transform = glm::translate(glm::mat4(1.0f), m_Transform->GetPosition()) * glm::toMat4(m_Transform->GetRotation());
		else
			transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) * glm::toMat4(glm::quat(glm::vec3(0.0f)));
	
		m_ViewMatrix = glm::inverse(transform);
	
		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
	
	}

}