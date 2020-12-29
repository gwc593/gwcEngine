#include "gepch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
#include "gwcEngine/Renderer/Renderer.h"

namespace gwcEngine
{

	OrthographicCamera::OrthographicCamera(uint32_t resX, uint32_t resY)
	{
		m_ProjectionMatrix = glm::ortho(-((float)resX / (float)resY) / 2.0f, ((float)resX / (float)resY )/ 2.0f, -0.5f, 0.5f, -100.0f, 100.0f);

		m_ViewMatrix = glm::mat4(1.0f);
		m_ResX = resX;
		m_ResY = resY;
		m_AspectRatio = (float)resX / (float)resY;

		m_FrameBufferSpec.Height = m_ResY;
		m_FrameBufferSpec.Width = m_ResX;
		m_FrameBuffer = FrameBuffer::Create(m_FrameBufferSpec);

		if (Renderer::GetAPI() == RendererAPI::API::DirectX) {
			m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
		}
		else {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		glDepthRange(-100.0f, 100.0f);
	}

	void OrthographicCamera::SetResolution(uint32_t resX, uint32_t resY)
	{
		m_ResX = resX; 
		m_ResY = resY; 
		SetAspectRatio((float)m_ResX / (float)m_ResY); 
		
		m_FrameBufferSpec.Height = resY;
		m_FrameBufferSpec.Width = resX;

		if (m_FrameBuffer != nullptr)
			m_FrameBuffer->Resize(resX, resY);

		m_OnResChange.raiseEvent(m_ResX, m_ResY);
	}

	void OrthographicCamera::SetAspectRatio(float aspectRatio)
	{
		m_ProjectionMatrix = glm::ortho(-aspectRatio / 2.0f, aspectRatio / 2.0f, -0.5f, 0.5f, -10.0f, 10.0f);
		m_AspectRatio = aspectRatio;
		CalculateViewMatrix();
	}

	bool OrthographicCamera::OnScreenResize(int width, int height )
	{
		SetResolution(width, height);
		return PROPAGATE_EVENT;
	}


}

