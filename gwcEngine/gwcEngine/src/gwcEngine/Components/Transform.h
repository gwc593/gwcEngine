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
		Transform()
		{
			m_Parent = nullptr;
			SetRotation({ 0.0f, 0.0f, 0.0f });
			m_Position = glm::vec3(0.0f);
			m_Scale = glm::vec3(1.0f);
			m_TransformMat = glm::mat4(1.0f);
		}

		glm::vec3 GetPosition() const 
		{
			return m_Position;
		}

		glm::quat GetRotation() const
		{ 
			return m_Rotation;
		}

		glm::vec3 GetScale() const
		{
			return m_Scale;
		}

		void SetPosition(glm::vec3 pos) 
		{ 
			m_Position = pos;
		}

		void SetScale(glm::vec3 scale) 
		{ 
			m_Scale = scale;
		}

		void SetRotation(glm::quat rot) 
		{ 
			m_Rotation = rot; 
		}
		void SetRotation(glm::vec3 erot) 
		{
			m_Rotation = glm::quat(erot); 
		}

		glm::mat4 GetTransformMatrix() { SetTansformMatrix(); return m_TransformMat; }

		void SetParent(const Transform& parent)
		{
			m_Parent = &parent;
		}

		void ClearParent()
		{
			m_Parent = nullptr;
		}
		
		
	private:

		glm::vec3 GetCompoundPosition() const
		{
			if (m_Parent == nullptr)
				return m_Position;
			else {
				return m_Position + m_Parent->GetPosition();
			}
		}

		glm::quat GetCompoundRotation() const
		{
			if (m_Parent == nullptr)
				return m_Rotation;
			else {
				return m_Rotation + m_Parent->GetRotation();
			}
		}

		glm::vec3 GetCompoundScale() const
		{
			if (m_Parent == nullptr)
				return m_Scale;
			else {
				return m_Scale * m_Parent->GetScale();
			}
		}

		void SetTansformMatrix()
		{
			//m_TransformMat = glm::translate(glm::mat4(1.0f), GetCompoundPosition()) * glm::mat4(GetCompoundRotation()) * glm::scale(glm::mat4(1.0f), GetCompoundScale()) ;
			m_TransformMat = glm::translate(glm::mat4(1.0f), GetCompoundPosition()) * glm::mat4(GetCompoundRotation()) * glm::scale(glm::mat4(1.0f), GetCompoundScale()) ;
		}
		glm::quat m_Rotation;
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::mat4 m_TransformMat;
		const Transform* m_Parent;
	};
}