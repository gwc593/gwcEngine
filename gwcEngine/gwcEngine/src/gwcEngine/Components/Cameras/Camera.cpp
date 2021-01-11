#include"gepch.h"
#include"Camera.h"
#include"gwcEngine/Renderer/Renderer.h"


namespace gwcEngine 
{
	void CameraBase::CalculateViewMatrix()
	{
	
		glm::mat4 transform;
		if (m_Transform != nullptr)
			m_ViewMatrix = glm::inverse(m_Transform->GetTransformMatrix());
		else
			m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) * glm::toMat4(glm::quat(glm::vec3(0.0f))));
	
		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
	
	}

	glm::vec3 CameraBase::ClipToWorldDirection(float  uX, float  uY)
	{
		CalculateViewMatrix();
		if(m_Transform != nullptr)
			return  glm::toMat4(m_Transform->GetRotation()) * glm::inverse(m_ProjectionMatrix) * glm::vec4(uX, uY, 1.0f, 1.0f);//this works!
		return glm::inverse(m_ProjectionMatrix) * glm::vec4(uX, uY, 1.0f, 1.0f);
	}

	Ray CameraBase::GenerateRay(float clipX, float clipY)
	{
		return Ray(m_Transform->GetPosition(), glm::normalize(ClipToWorldDirection(clipX, clipY)),1000.0f);
	}
}