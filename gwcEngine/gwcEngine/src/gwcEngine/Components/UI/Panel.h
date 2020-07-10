#pragma once
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Mesh.h"

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
		
	private:

		uint32_t m_Width;
		uint32_t m_Height;
		float m_AspectRatio;

		FrameBufferSpecification m_PanelSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Mesh m_DrawArea;
	};
}