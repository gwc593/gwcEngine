#pragma once
#include<glm/glm.hpp>
#include "gwcEngine/Renderer/Cameras/Camera.h"
namespace gwcEngine
{

	class OrthographicCamera: public Camera
	{
	public:
		OrthographicCamera(float aspectRatio = 1.79);
		
		void SetAspectRatio(float aspectRatio);

		inline glm::mat4 GetProjectMatrix() override{			return m_ProjectionMatrix; }
		inline glm::mat4 GetViewtMatrix() override{				return m_ViewMatrix; }
		inline glm::mat4 GetViewProjectionMatrix() override {	return m_ViewProjectionMatrix; }

		inline void SetPosition(const glm::vec3& position) override{	m_Position = position; CalculateViewMatrix();}
		inline void SetRotation(const float rotation){m_Rotation = rotation; CalculateViewMatrix();}

		inline const glm::vec3& GetPostion() const override { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		inline const float GetAspectRatio()const override { return m_AspectRatio; }

		bool OnScreenResize(int width, int height);
	private:

		void CalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
		float m_AspectRatio;
	};
}