#pragma once
#include <glm/glm.hpp>
namespace gwcEngine
{
	class Ray
	{
	public:
		Ray() = default;
		
		Ray(const glm::vec3& o, const glm::vec3& d, float length = 1.0f) :m_Origin(o), m_Direction(glm::normalize(d)), m_Length(length) {};

		~Ray() = default;
	
		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }
		const float& GetLength() const { return m_Length; }
	private:

		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
		float m_Length;
	};
}
