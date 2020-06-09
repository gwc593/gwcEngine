#include"gepch.h"
#include "PerspectiveCamera.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
namespace gwcEngine
{

	PerspectiveCamera::PerspectiveCamera(float FOV, float ARatio, float NClip, float FClip):
		m_FOV(FOV), m_AspectRatio(ARatio),m_NearClip(NClip),m_FarClip(FClip),
		m_ProjectionMatrix(glm::perspective(FOV,ARatio,NClip,FClip)),m_ViewMatrix(glm::mat4(1.0f))
	{
		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		SetRotation(glm::vec3(0.0f));
		m_Position = glm::vec3(0.0f,0.0f,3.0f);
		CalculateProjectionMatrix();
		CalculateViewMatrix();

		//todo set depth buffer range to be consistent with the clipping planes of the camera
		glDepthRange(m_NearClip, m_FarClip);

	}

	void PerspectiveCamera::SetRotation(const glm::vec3& eulerRotation)
	{
		m_Rotation = glm::quat(eulerRotation);
		CalculateViewMatrix();
	}

	void PerspectiveCamera::SetRotation(glm::quat rotation)
	{
		m_Rotation = rotation;
		CalculateViewMatrix();
	}

	glm::quat PerspectiveCamera::GetRotation() const
	{
		return m_Rotation;
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation);
		//glm::mat4 transform = glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0.0f,0.0f,1.0f))* glm::translate(glm::mat4(1.0f), m_Position);

		m_ViewMatrix = glm::inverse(transform);

		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
	}

	void PerspectiveCamera::CalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	}

}


