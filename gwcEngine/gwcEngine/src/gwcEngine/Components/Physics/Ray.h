#pragma once
#include <glm/glm.hpp>
#include "gwcEngine/Renderer/Cameras/Camera.h"
namespace gwcEngine
{
	class Ray
	{
	public:
		Ray() = default;
		
		Ray(const glm::vec3& o, const glm::vec3& d) :m_Origin(o), m_Direction(d) {};

		Ray(const Ref<Camera>& camera, float clipX, float clipY);

		~Ray() = default;
	
		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }
	
		
	private:

		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
	};
}
