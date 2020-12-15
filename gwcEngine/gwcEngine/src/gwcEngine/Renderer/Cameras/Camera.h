#pragma once
#include "glm/glm.hpp"
#include "gwcEngine/Core/Window.h"
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Transform.h"
namespace gwcEngine
{
	class Renderer;
	class CameraBase
	{
	public:

		virtual glm::mat4 GetProjectMatrix() = 0; 
		virtual glm::mat4 GetViewtMatrix() = 0;
		virtual glm::mat4 GetViewProjectionMatrix() = 0;

		void CalculateViewMatrix();


		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual const glm::vec3& GetPostion() const = 0;

		virtual void SetResolution(uint32_t resX, uint32_t resY) = 0;
		virtual const float GetAspectRatio() const = 0;

		virtual glm::vec3 ScreenToWorld(int32_t x, int32_t y, const Window& window) = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual Ref<FrameBuffer> GetFrameBuffer() const = 0;

		virtual void SetClearColour(glm::vec4 colour) = 0;
		virtual glm::vec4 GetClearColour() const= 0;

		void SetTransformRef(Ref<Transform> transform) { 
			m_Transform = transform;
			CalculateViewMatrix(); 
		}

	protected:
		uint32_t m_ResX, m_ResY;
		float m_AspectRatio;
		FrameBufferSpecification m_FrameBufferSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Transform> m_Transform;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec4 m_ClearColour;

	};

	using Camera = gwcEngine::Ref<gwcEngine::CameraBase>;
}