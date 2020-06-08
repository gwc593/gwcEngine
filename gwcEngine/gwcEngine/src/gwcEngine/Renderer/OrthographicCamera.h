#pragma once
#include<glm/glm.hpp>

namespace gwcEngine
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline glm::mat4 GetProjectMatrix() {			return m_ProjectionMatrix; }
		inline glm::mat4 GetViewtMatrix() {				return m_ViewMatrix; }
		inline glm::mat4 GetViewProjectionMatrix() {	return m_ViewProjectionMatrix; }

		inline void SetPosition(const glm::vec3& position){	m_Position = position; CalculateViewMatrix();}
		inline void SetRotation(const float rotation){m_Rotation = rotation; CalculateViewMatrix();}

		inline const glm::vec3& GetPostion() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

	private:

		void CalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}