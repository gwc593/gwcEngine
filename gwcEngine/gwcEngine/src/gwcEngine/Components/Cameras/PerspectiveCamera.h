#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "gwcEngine/Events/Event.h"
#include "gwcEngine/Components/Cameras/Camera.h"
namespace gwcEngine
{

	class PerspectiveCamera : public CameraBase
	{
	public:
		PerspectiveCamera(float FOV, uint32_t resX, uint32_t resY, float NClip, float FClip, Ref<Transform> transform = nullptr);


		
		inline Ref<FrameBuffer> GetFrameBuffer() const override { return m_FrameBuffer; }
		
		inline bool OnFrameResize(int width, int height)
		{
			if (width != 0 && height != 0) {
				m_FrameBufferSpec.Height = height;
				m_FrameBufferSpec.Width = width;
				m_FrameBuffer->Resize(width, height);
				SetResolution(width, height);
			}
			return PROPAGATE_EVENT;
		}

		inline void SetResolution(uint32_t resX, uint32_t resY) override; 
		inline void SetFOV(float FOV) { m_FOV = FOV; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetNClip(float NClip) { m_NearClip = NClip; CalculateProjectionMatrix(); CalculateViewMatrix(); }
		inline void SetFClip(float FClip) { m_FarClip = FClip; CalculateProjectionMatrix();  CalculateViewMatrix(); }



		inline float GetFOV() { return m_FOV; }
		inline const float GetAspectRatio() const override { return m_AspectRatio; }
		inline float GetNClip() { return m_NearClip; }
		inline float GetFClip() { return m_FarClip; }

		void SetRotation(const glm::vec3& eulerRotation);
		void SetRotation(glm::quat rotation);

		inline glm::quat GetRotation() const;

		glm::vec4 GetClearColour() const override { return m_ClearColour; }
		void SetClearColour(glm::vec4 colour) override { m_ClearColour = colour; }

		uint32_t GetWidth() const override { return m_ResX; }
		uint32_t GetHeight() const override { return m_ResY; }

	private:

		inline void SetAspectRatio(float ARatio) { m_AspectRatio = ARatio; CalculateProjectionMatrix(); CalculateViewMatrix(); }

		void CalculateProjectionMatrix();
	private:

		float m_FOV;
		float m_NearClip;
		float m_FarClip;
		
	};
}