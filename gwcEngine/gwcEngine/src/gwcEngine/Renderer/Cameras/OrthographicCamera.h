#pragma once
#include<glm/glm.hpp>
#include "gwcEngine/Renderer/Cameras/Camera.h"

namespace gwcEngine
{

	class OrthographicCamera: public Camera
	{
	public:
		OrthographicCamera(uint32_t resX = 800, uint32_t resY= 600);
		
		inline void SetResolution(uint32_t resX, uint32_t resY) override; 

		inline glm::mat4 GetProjectMatrix() override{			return m_ProjectionMatrix; }
		inline glm::mat4 GetViewtMatrix() override{				return m_ViewMatrix; }
		inline glm::mat4 GetViewProjectionMatrix() override {	return m_ViewProjectionMatrix; }

		inline void SetPosition(const glm::vec3& position) override{	m_Position = position; CalculateViewMatrix();}
		inline void SetRotation(const float rotation){m_Rotation = rotation; CalculateViewMatrix();}

		inline const glm::vec3& GetPostion() const override { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		inline const float GetAspectRatio()const override { return m_AspectRatio; }

		bool OnScreenResize(int width, int height);

		glm::vec3 ScreenToWorld(uint32_t x, uint32_t y, const Window& window) override;

		Ref<FrameBuffer> GetFrameBuffer() const override { return m_FrameBuffer; }

		glm::vec4 GetClearColour() const override { return m_ClearColour; }
		void SetClearColour(glm::vec4 colour) override { m_ClearColour = colour; }

		uint32_t GetWidth() const override { return m_ResX; }
		uint32_t GetHeight() const override { return m_ResY; }
	private:

		void SetAspectRatio(float aspectRatio);
		void CalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec4 m_ClearColour;

		glm::vec3 m_Position;
		float m_Rotation;
		float m_AspectRatio;

		FrameBufferSpecification m_FrameBufferSpec;
		Ref<FrameBuffer> m_FrameBuffer;

		uint32_t m_ResX, m_ResY;

	};
}