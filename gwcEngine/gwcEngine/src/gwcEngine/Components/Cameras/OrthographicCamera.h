#pragma once
#include<glm/glm.hpp>
#include "gwcEngine/Components/Cameras/Camera.h"

namespace gwcEngine
{

	class OrthographicCamera: public CameraBase
	{
	public:
		OrthographicCamera(uint32_t resX = 800, uint32_t resY= 600);
		
		inline void SetResolution(uint32_t resX, uint32_t resY) override; 

		inline const float GetAspectRatio()const override { return m_AspectRatio; }

		bool OnScreenResize(int width, int height);

		Ref<FrameBuffer> GetFrameBuffer() const override { return m_FrameBuffer; }

		glm::vec4 GetClearColour() const override { return m_ClearColour; }
		void SetClearColour(glm::vec4 colour) override { m_ClearColour = colour; }

		uint32_t GetWidth() const override { return m_ResX; }
		uint32_t GetHeight() const override { return m_ResY; }
	private:

		void SetAspectRatio(float aspectRatio);

	};
}