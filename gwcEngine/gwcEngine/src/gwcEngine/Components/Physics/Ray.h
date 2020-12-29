#pragma once
#include <glm/glm.hpp>
namespace gwcEngine
{
	class Ray
	{
	public:
		Ray() = default;
		
		Ray(const glm::vec3& o, const glm::vec3& d) :m_Origin(o), m_Direction(d) {};

		~Ray() = default;
	
		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }
	
		
	private:

		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
	};
}
