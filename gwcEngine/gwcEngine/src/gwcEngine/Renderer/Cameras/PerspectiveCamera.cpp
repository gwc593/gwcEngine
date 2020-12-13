#include"gepch.h"
#include "PerspectiveCamera.h"
#include "gwcEngine/Renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>

#include "gwcEngine/Core/application.h"
namespace gwcEngine
{

	PerspectiveCamera::PerspectiveCamera(float FOV, uint32_t resX, uint32_t resY, float NClip, float FClip):
		m_FOV(FOV), 
		m_NearClip(NClip),
		m_FarClip(FClip),
		m_ProjectionMatrix(glm::perspective(FOV, (float)resX / (float)resY,NClip,FClip)),m_ViewMatrix(glm::mat4(1.0f))
	{
		m_ResX = resX;
		m_ResY = resY;
		m_AspectRatio = (float)resX / (float)resY;

		m_FrameBufferSpec.Height = m_ResY;
		m_FrameBufferSpec.Width = m_ResX;
		m_FrameBufferSpec.NClip = m_NearClip;
		m_FrameBufferSpec.FClip = m_FarClip;
		m_FrameBuffer = FrameBuffer::Create(m_FrameBufferSpec);

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

		
		glDepthRange(m_NearClip, m_FarClip);
	}

	void PerspectiveCamera::SetResolution(uint32_t resX, uint32_t resY)
	{
		m_ResX = resX; 
		m_ResY = resY; 
		SetAspectRatio((float)m_ResX / (float)m_ResY);

		m_FrameBufferSpec.Width = resX;
		m_FrameBufferSpec.Height = resY;

		if (m_FrameBuffer != nullptr)
			m_FrameBuffer->Resize(resX, resY);
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


