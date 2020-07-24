#pragma once
#include "glm/glm.hpp"
#include "gwcEngine/Core/Window.h"
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

		virtual const float GetAspectRatio() const = 0;

		virtual glm::vec3 ScreenToWorld(uint32_t x, uint32_t y, const Window& window) = 0;
	};
}