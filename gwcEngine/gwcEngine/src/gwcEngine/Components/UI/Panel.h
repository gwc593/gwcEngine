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
		Panel(uint32_t width, uint32_t height, Ref<OrthographicCamera> camera);
		   
		static enum class Anchor
		{
			TopLeft = 0,
			TopRight,
			BottomLeft,
			BottomRight,
			Center
		};

		bool OnSizeChange(uint32_t width, uint32_t height);
		bool OnMainWindowSizeChange(int width, int height);
		void SetShader(const Ref<Shader>& shader) { m_UIShader = shader; }
		void Bind();
		void Unbind();
		void flush();
		const Ref<Camera> GetCamera() const { return m_PanelCamera; }
		
	private:

		uint32_t m_Width, m_MainWindowWidth;
		uint32_t m_Height, m_MainWindowHeight;
		float m_AspectRatio;
		float m_mainAspect;

		FrameBufferSpecification m_PanelSpec;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Shader> m_UIShader;
		Ref<Shader> m_DefaultShader;
		Mesh m_DrawArea;
		Ref<OrthographicCamera> m_PanelCamera;
	
	private://Callbacks
		Ref<EventCallback<int, int>> c_OnMainWindowSizeChange;
		//EventCallback<uint32_t, uint32_t> c_OnPanelSizeChange;

	};
}