#pragma once
#include "gwcEngine/Renderer/FrameBuffer.h"
#include "gwcEngine/Components/Renderable/Mesh.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Cameras/Camera.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Components/Physics/Ray.h"
namespace gwcEngine
{
	enum class Anchor
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
		Panel(uint32_t width, uint32_t height, Ref<Transform> mainTrans , Ref<CameraBase> capturingCamera = nullptr, Ref<CameraBase> renderingCamera = std::dynamic_pointer_cast<gwcEngine::CameraBase>(Application::Get()->GetWindow().GetCamera()));
		~Panel();
		static Ref<Panel> Create(uint32_t width, uint32_t height, Ref<Transform> mainTrans, Ref<CameraBase> capturingCamera = nullptr, Ref<CameraBase> renderingCamera = std::dynamic_pointer_cast<gwcEngine::CameraBase>(Application::Get()->GetWindow().GetCamera()));

		void SetSize(uint32_t width, uint32_t height);
		void SetPosition(int x, int y, Anchor relativeTo = Anchor::Center);
		std::tuple<int32_t, int32_t> GetCenter(Anchor relativeTo = Anchor::Center);
		
		/// @brief get clip space position of a screen space mouse cordinat (pixel on full window)
		/// @param x x-Pixel of full window
		/// @param y y-Pixel of full window
		/// @return vec2 of clip space position of the 'capture' shown within the panel
		glm::vec2 GetScreenToClipSpacePosition(float x, float y);

		uint8_t GetDepth(float x, float y);

		void flush();

		uint32_t GetWidth()const { return m_Width; }
		uint32_t GetHeight()const { return m_Height; }
		
		const Ref<CameraBase> GetCamera() const { return m_RenderingCamera; }
		void SetCaptureCamera(const Ref<CameraBase>& camera);
		
		bool OnMouseMovedHandler(float x, float y);

		Ray GetWorldRay(float x, float y);
		Ray GetWorldRay(std::pair<float, float> pos) { return GetWorldRay(pos.first, pos.second); };

		static std::vector<std::weak_ptr<Panel>> s_Panels;
	private://data

		uint32_t m_Width;
		uint32_t m_Height;
		std::tuple<int32_t,int32_t> m_Center;
		float m_AspectRatio;

		Ref<Shader> m_UnlitTextureShader;
		Ref<Shader> m_DefaultShader;
		Mesh m_RenderPlane;

		Ref<CameraBase> m_RenderingCamera;
		Ref<CameraBase> m_CapturingCamera;

		Ref<Transform> m_MainTransform;
		Transform m_RenderPlaneTransform;
		Anchor m_Anchor;

		bool isHeld = false;
		int xHeld = 0;
		int yHeld = 0;
		std::tuple<int32_t, int32_t> currentPos;
		

	public://Callbacks
		Ref<EventCallback<int, int>> c_OnMainWindowSizeChange;
		Ref<EventCallback<float, float>> c_OnMouseMoved;
	private://methods
		bool OnMainWindowSizeChangeHandler(int width, int height);

		void DragPanel(float x, float y);

		bool OnCaptResChange(uint32_t resx, uint32_t resy);
		Ref<EventCallback<uint32_t, uint32_t>> m_OnCaptureResChangeCB;

	private://Events;
		Event<> e_OnCursorEnter;
		Event<> e_OnCursorExit;
		Event<> e_OnClosed;
	};
}