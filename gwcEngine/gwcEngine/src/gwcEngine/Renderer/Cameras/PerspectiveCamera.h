#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "gwcEngine/Events/Event.h"
#include "gwcEngine/Renderer/Cameras/Camera.h"
namespace gwcEngine
{

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float FOV, float ARatio, float NClip, float FClip);

		inline void SetFOV(float FOV) { m_FOV = FOV; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetAspectRatio(float ARatio) { m_AspectRatio = ARatio; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetNClip(float NClip) { m_NearClip = NClip; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetFClip(float FClip) { m_FarClip = FClip; CalculateProjectionMatrix();  CalculateViewMatrix(); }

		inline bool OnFrameResize(int width, int height)
		{
			if (width != 0 && height != 0) {
				SetAspectRatio((float)width / (float)height),
				CalculateProjectionMatrix();
				CalculateViewMatrix();
			}
			return PROPAGATE_EVENT;
		}

		inline float GetFOV() { return m_FOV; }
		inline float GetAspectRatio() { return m_AspectRatio; }
		inline float GetNClip() { return m_NearClip; }
		inline float GetFClip() { return m_FarClip; }

		inline glm::mat4 GetProjectMatrix() override{ return m_ProjectionMatrix; }
		inline glm::mat4 GetViewtMatrix() override{ return m_ViewMatrix; }
		inline glm::mat4 GetViewProjectionMatrix() override{ return m_ViewProjectionMatrix; }

		inline void SetPosition(const glm::vec3& position) override{ m_Position = position; CalculateViewMatrix(); }

		void SetRotation(const glm::vec3& eulerRotation);
		void SetRotation(glm::quat rotation);

		inline const glm::vec3& GetPostion() const override { return m_Position; }
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