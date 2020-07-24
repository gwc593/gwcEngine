#pragma once
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Mesh.h"
#include "gwcEngine/Components/Transform.h"

#include "gwcEngine/Renderer/Renderer.h"
#include "gwcEngine/Renderer/RenderCommand.h"


namespace gwcEngine
{
	static enum class Anchor
	{
		Center = 0,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	class Panel
	{
	public:
		Panel(uint32_t width, uint32_t height, Ref<Camera> renderingCamera, Ref<Camera> capturingCamera = nullptr);

		void SetSize(uint32_t width, uint32_t height);
		void SetPosition(int x, int y, Anchor relativeTo = Anchor::Center);
		void Bind();
		void Unbind();
		void flush();

		uint32_t GetWidth()const { return m_Width; }
		uint32_t GetHeight()const { return m_Height; }
		
		const Ref<Camera> GetCamera() const { return m_RenderingCamera; }
		
		bool OnMouseMovedHandler(float x, float y);
	private://data

		uint32_t m_Width, m_MainWindowWidth;
		uint32_t m_Height, m_MainWindowHeight;
		float m_AspectRatio;
		float m_MainAspect;

		FrameBufferSpecification m_PanelSpec;
		Ref<FrameBuffer> m_FrameBuffer;

		Ref<Shader> m_UnlitTextureShader;
		Ref<Shader> m_DefaultShader;
		Mesh m_RenderPlane;

		Ref<Camera> m_RenderingCamera;
		Ref<Camera> m_CapturingCamera;
		glm::vec2 m_Position;

		Transform m_MainTransform;
		Transform m_RenderPlaneTransform;



	public://Callbacks
		Ref<EventCallback<int, int>> c_OnMainWindowSizeChange;
		Ref<EventCallback<float, float>> c_OnMouseMoved;
	private://methods
		glm::vec2 PixelsToScreenSpace(int x, int y);
		bool OnMainWindowSizeChangeHandler(int width, int height);

	private://Events;
		Event<> e_OnCursorEnter;
		Event<> e_OnCursorExit;
		Event<> e_OnClosed;
	};
}