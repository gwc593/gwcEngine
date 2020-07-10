#include "gepch.h"
#include "Panel.h"

namespace gwcEngine
{
	Panel::Panel(uint32_t width, uint32_t height) 
		:m_Width(width), m_Height(height)
	{

		m_AspectRatio = m_Width / m_Height;

		m_PanelSpec.Height = m_Height;
		m_PanelSpec.Width = m_Width;

		m_FrameBuffer = FrameBuffer::Create(m_PanelSpec);

#pragma region QuadMeshData

		gwcEngine::BufferLayout layout = {
				{gwcEngine::ShaderDataType::Float3, "a_Position"},
				{gwcEngine::ShaderDataType::Float2, "a_TexCoord"}
		};

		float verticesQuad[4 * 5] = {
			// ----------Position--------------// -- Texture coordinates----- 
				m_AspectRatio, (1.0f / m_AspectRatio), 0.0f,      1.0f, 1.0f,
				m_AspectRatio,-(1.0f / m_AspectRatio), 0.0f,      1.0f, 0.0f,
			   -m_AspectRatio,-(1.0f / m_AspectRatio), 0.0f,      0.0f, 0.0f,
			   -m_AspectRatio, (1.0f / m_AspectRatio), 0.0f,      0.0f, 1.0f
		};
		//f   t   v
		uint32_t indicesQuad[1 * 2 * 3] = {
			0,1,2,
			0,2,3,
		};
#pragma endregion

		m_DrawArea.SetVertexBuffer(verticesQuad, sizeof(verticesQuad), layout);

		//make mesh dynamic to allow for panel resizing isDynamic = true.
		m_DrawArea.SetIndexBuffer(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t), true);
	}
}