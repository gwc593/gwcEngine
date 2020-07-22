#include "gepch.h"
#include "OrthographicCamera.h"
#include "gwcEngine/Renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
namespace gwcEngine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
	{
		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		m_Rotation = 0.0f;
		m_Position = glm::vec3(0.0f);
		glDepthRange(-100.0f, 100.0f);
	}

	void OrthographicCamera::SetSize(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
		CalculateViewMatrix();
	}


	void OrthographicCamera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);

		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

	}

	bool OrthographicCamera::OnScreenResize(int width, int height)
	{
		float AspecRatio = (float)width / (float)height;
		float AspecRatioInv = (float)height / (float)width;
		SetSize(-AspecRatio, AspecRatio, -AspecRatioInv, AspecRatioInv);
		return PROPAGATE_EVENT;
	}
}

