#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
namespace gwcEngine
{

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float FOV, float ARatio, float NClip, float FClip);

		inline void SetFOV(float FOV) { m_FOV = FOV; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetAspectRatio(float ARatio) { m_AspectRatio = ARatio; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetNClip(float NClip) { m_NearClip = NClip; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetFClip(float FClip) { m_FarClip = FClip; CalculateProjectionMatrix();  CalculateViewMatrix(); }

		inline float GetFOV() { return m_FOV; }
		inline float GetAspectRatio() { return m_AspectRatio; }
		inline float GetNClip() { return m_NearClip; }
		inline float GetFClip() { return m_FarClip; }

		inline glm::mat4 GetProjectMatrix() { return m_ProjectionMatrix; }
		inline glm::mat4 GetViewtMatrix() { return m_ViewMatrix; }
		inline glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }

		inline void SetRotation(const glm::vec3& eulerRotation);
		inline void SetRotation(glm::quat rotation);

		inline const glm::vec3& GetPostion() const { return m_Position; }
		inline glm::quat GetRotation() const;

	private:

		void CalculateViewMatrix();
		void CalculateProjectionMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::quat m_Rotation;

		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;
	};
}