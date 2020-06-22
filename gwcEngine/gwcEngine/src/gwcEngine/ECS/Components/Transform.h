#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gwcEngine
{
	class Transform
	{
	public:
		glm::vec3 GetPosition() { return m_Position; }
		glm::quat GetRotation() { return m_Rotation; }
		
		void SetPosition(glm::vec3 pos) {  m_Position = pos; }
		void SetRotation(glm::quat rot) { m_Rotation = rot; }
		void SetRotation(glm::vec3 erot) { m_Rotation = glm::quat(erot); }

	private:
		glm::quat m_Rotation;
		glm::vec3 m_Position;

	};
}