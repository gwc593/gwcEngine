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

		void SetPosition(glm::vec3 pos) { m_Position = pos; }
		void SetScale(glm::vec3 scale) { m_Scale = scale; }

		void SetRotation(glm::quat rot) { m_Rotation = rot; }
		void SetRotation(glm::vec3 erot) { m_Rotation = glm::quat(erot); }

		glm::mat4 GetTransformMatrix() { SetTansformMatrix(); return m_TransformMat; }

		
		
	private:
		void SetTansformMatrix()
		{
			m_TransformMat = glm::scale(glm::mat4(1.0f), m_Scale) * glm::translate(glm::mat4(1.0f), m_Position) *glm::mat4(m_Rotation);
		}
		glm::quat m_Rotation;
		glm::vec3 m_Position;
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::mat4 m_TransformMat = glm::mat4(1.0f);

	};
}