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
		Panel(uint32_t width, uint32_t height, Ref<Camera> camera);
		   
		static enum class Anchor
		{
			Center = 0,
			TopLeft,
			TopRight,
			BottomLeft,
			BottomRight
		};

		void SetSize(uint32_t width, uint32_t height);
		void SetPosition(int x, int y, Anchor relativeTo = Anchor::Center);
		bool OnSizeChange(uint32_t width, uint32_t height);
		bool OnMainWindowSizeChange(int width, int height);
		void Bind();
		void Unbind();
		void flush();

		uint32_t GetWidth()const { return m_Width; }
		uint32_t GetHeight()const { return m_Height; }
		
		const Ref<Camera> GetCamera() const { return m_PanelCamera; }
		
	private://data

		uint32_t m_Width, m_MainWindowWidth;
		uint32_t m_Height, m_MainWindowHeight;
		float m_AspectRatio;
		float m_MainAspect;

		FrameBufferSpecification m_PanelSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Shader> m_UnlitTextureShader;
		Ref<Shader> m_DefaultShader;
		Mesh m_DrawArea;
		Ref<Camera> m_PanelCamera;

		glm::vec2 m_Position;
	#
	private://methods
		glm::vec2 PixelsToScreenSpace(int x, int y);

	private://Callbacks
		Ref<EventCallback<int, int>> c_OnMainWindowSizeChange;
		//EventCallback<uint32_t, uint32_t> c_OnPanelSizeChange;
	};
}