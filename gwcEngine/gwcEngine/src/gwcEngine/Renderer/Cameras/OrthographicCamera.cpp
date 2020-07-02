#include "gepch.h"
#include "OrthographicCamera.h"
#include "gwcEngine/Renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
namespace gwcEngine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left,right,bottom,top,-1.0f,1.0f)), m_ViewMatrix(1.0f)
	{
		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		m_Rotation = 0.0f;
		m_Position = glm::vec3(0.0f);
		glDepthRange(0.0f, 1.0f);
	}

	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0.0f,0.0f,1.0f));

		m_ViewMatrix = glm::inverse(transform);

		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
		
	}

}

