#pragma once
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Mesh.h"

#include "gwcEngine/Renderer/Renderer.h"
#include "gwcEngine/Renderer/RenderCommand.h"


namespace gwcEngine
{


	class Panel
	{
	public:
		Panel(uint32_t width, uint32_t height);
		   
		static enum class Anchor
		{
			TopLeft = 0,
			TopRight,
			BottomLeft,
			BottomRight,
			Center
		};

		bool OnSizeChange(uint32_t width, uint32_t height);

		void SetShader(const Ref<Shader>& shader) { m_UIShader = shader; }
		void Bind();
		void Unbind();
		void flush();
		
	private:

		uint32_t m_Width;
		uint32_t m_Height;
		float m_AspectRatio;

		FrameBufferSpecification m_PanelSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Shader> m_UIShader;
		Mesh m_DrawArea;
	};
}