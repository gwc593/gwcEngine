#pragma once
#include "glm/glm.hpp"
#include "gwcEngine/Core/Window.h"
#include "gwcEngine/Renderer/FrameBuffer.h"
namespace gwcEngine
{
	class Camera
	{
	public:

		virtual glm::mat4 GetProjectMatrix() = 0; 
		virtual glm::mat4 GetViewtMatrix() = 0;
		virtual glm::mat4 GetViewProjectionMatrix() = 0;

		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual const glm::vec3& GetPostion() const = 0;

		virtual void SetResolution(uint32_t resX, uint32_t resY) = 0;
		virtual const float GetAspectRatio() const = 0;

		virtual glm::vec3 ScreenToWorld(uint32_t x, uint32_t y, const Window& window) = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual Ref<FrameBuffer> GetFrameBuffer() const = 0;

		virtual void SetClearColour(glm::vec4 colour) = 0;
		virtual glm::vec4 GetClearColour() const= 0;

	protected:
		uint32_t m_ResX, m_ResY;
		float m_AspectRatio;
		FrameBufferSpecification m_FrameBufferSpec;
		Ref<FrameBuffer> m_FrameBuffer;

	};
}