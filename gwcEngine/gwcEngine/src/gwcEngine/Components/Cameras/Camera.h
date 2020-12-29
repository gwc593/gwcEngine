#pragma once
#include "gwcEngine/Core/Window.h"
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Physics/Ray.h"
namespace gwcEngine
{
	class CameraBase
	{
	public:

		void CalculateViewMatrix();

		glm::vec3 ClipToWorld(float  uX, float  uY);


		void SetTransformRef(Ref<Transform> transform)
		{
			m_Transform = transform;
			CalculateViewMatrix();
		}

		const Ref<Transform> GetTransform() const { return m_Transform; }

		const Event<uint32_t, uint32_t>& GetOnResolutionChangeEvent()const { return m_OnResChange; }

		Ray GenerateRay(float clipX, float clipY);

		//virtual methods
		glm::mat4 GetProjectMatrix() { CalculateViewMatrix();  return m_ProjectionMatrix; }
		glm::mat4 GetViewtMatrix(){CalculateViewMatrix(); return m_ViewMatrix;}
		glm::mat4 GetViewProjectionMatrix() { CalculateViewMatrix(); return m_ViewProjectionMatrix; }

		virtual void SetResolution(uint32_t resX, uint32_t resY) = 0;
		virtual const float GetAspectRatio() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual Ref<FrameBuffer> GetFrameBuffer() const = 0;

		virtual void SetClearColour(glm::vec4 colour) = 0;
		virtual glm::vec4 GetClearColour() const= 0;


	protected:
		uint32_t m_ResX, m_ResY;
		float m_AspectRatio;
		FrameBufferSpecification m_FrameBufferSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Transform> m_Transform;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec4 m_ClearColour = { 0.65f,0.65f,0.65f,1.0f };
		Event<uint32_t, uint32_t> m_OnResChange;

	};

	using Camera = gwcEngine::Ref<gwcEngine::CameraBase>;
}