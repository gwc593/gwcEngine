#include "gepch.h"
#include "Panel.h"
#include "gwcEngine/Core/application.h"
#include "gwcEngine/Core/Input.h"
#include "gwcEngine/Renderer/Renderer.h"
namespace gwcEngine
{
	std::vector<Ref<Panel>> Panel::s_Panels;

	Panel::Panel(uint32_t width, uint32_t height, Ref<CameraBase> capturingCamera, Ref<CameraBase> renderingCamera)
		:m_Width(width), m_Height(height),m_RenderingCamera(renderingCamera), m_CapturingCamera(capturingCamera), m_Anchor(gwcEngine::Anchor::Center)
	{
		if (capturingCamera == nullptr)
			m_CapturingCamera = m_RenderingCamera;

		m_OnCaptureResChangeCB.reset(new EventCallback<uint32_t, uint32_t>([this](uint32_t x, uint32_t y) { return this->OnCaptResChange(x, y);  }));
		m_CapturingCamera->GetOnResolutionChangeEvent().subscribe(m_OnCaptureResChangeCB);

		//get window and panel geometry

		m_AspectRatio = (float)m_Width / (float)m_Height;
		
		//create unit quad to render draw.
		m_RenderPlane = Mesh::Quad();


		//setup callbacks
		c_OnMainWindowSizeChange = CreateRef<EventCallback<int, int>>();
		c_OnMainWindowSizeChange->SetCallback(BIND_EVENT_FN(Panel::OnMainWindowSizeChangeHandler));
		Application::Get()->GetWindow().GetWindowResizeEvent().subscribe(c_OnMainWindowSizeChange);

		c_OnMouseMoved = CreateRef<EventCallback<float, float>>();
		//c_OnMouseMoved->SetCallback([&](float& x, float& y) {GE_TRACE("{0}, {1}",x,y); return false; });
		c_OnMouseMoved->SetCallback(BIND_EVENT_FN(Panel::OnMouseMovedHandler));
		Input::GetMouseMovedEvent().subscribe(c_OnMouseMoved);

		//setup panel shader
		m_UnlitTextureShader = gwcEngine::Shader::Create("assets/Shaders/PanelCapture.glsl");
		m_DefaultShader = gwcEngine::Shader::Create("assets/Shaders/PanelBackground.glsl");

		m_UnlitTextureShader->UploadUniformFloat("u_border_width", 0.001f);
		m_DefaultShader->UploadUniformFloat("u_border_width", 0.001f);


		m_RenderPlaneTransform.SetPosition(glm::vec3(0.0f,0.0f, 0.2f));
		
		m_RenderPlaneTransform.SetParent(m_MainTransform);


		float  WS = ((float)m_Width / (float)m_RenderingCamera->GetWidth()) * m_RenderingCamera->GetAspectRatio();
		float HS = ((float)m_Height / (float)m_RenderingCamera->GetHeight());
		m_MainTransform.SetScale(glm::vec3(WS, HS, 1.0f));
		m_MainTransform.SetPosition(glm::vec3((0.0f, 0.0f, -0.2f)));

		SetPosition(0, 0);

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}
	}

	Ref<Panel> Panel::Create(uint32_t width, uint32_t height, Ref<CameraBase> capturingCamera, Ref<CameraBase> renderingCamera)
	{
		auto temp = CreateRef<Panel>(width, height, capturingCamera, renderingCamera);
		s_Panels.push_back(temp);
		return temp;
	}

	void Panel::SetSize(uint32_t width, uint32_t height)
	{
		currentPos = GetCenter(Anchor::TopLeft);
		
		m_Width = width;
		m_Height = height;
		m_AspectRatio = (float)width / (float)height;

		float  WS = ((float)m_Width / (float)m_RenderingCamera->GetWidth()) * m_RenderingCamera->GetAspectRatio();
		float HS = ((float)m_Height / (float)m_RenderingCamera->GetHeight());
		m_MainTransform.SetScale(glm::vec3(WS, HS, 1.0f));
		m_MainTransform.SetPosition(glm::vec3((0.0f, 0.0f, -0.2f)));

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}

		SetPosition(std::get<0>(currentPos), std::get<1>(currentPos), Anchor::TopLeft);
	}

	void Panel::SetPosition(int x, int y, Anchor relativeTo)
	{
		int xp = 0;
		int yp = 0;


		switch (relativeTo) {
			case Anchor::TopLeft:{ break; }
			case Anchor::TopRight: { xp = m_RenderingCamera->GetWidth(); break; }
			case Anchor::BottomLeft: {yp = m_RenderingCamera->GetHeight();  break; }
			case Anchor::BottomRight:{xp = m_RenderingCamera->GetWidth(); yp = m_RenderingCamera->GetHeight(); break; }
			case Anchor::Center: {xp = m_RenderingCamera->GetWidth() / 2; yp = m_RenderingCamera->GetHeight() / 2; break; }
		}

		m_Anchor = relativeTo;
		m_Center = { x,y};

		//generate clip space position
		auto& window = Application::Get()->GetWindow();
		float mX, mY, cx, cy, uX, uY;

		mX = (2.0f) / (float(window.GetWidth()));
		mY = (-2.0f) / (float(window.GetHeight()));

		cx = 1.0f - (mX * float(window.GetWidth()));
		cy = 1.0f + (mY * float(window.GetHeight()));


		uX = (mX * (float)(x + xp)) + cx;
		uY = (mY * (float)(y + yp)) - cy;

		auto temp = m_RenderingCamera->ClipToWorld(uX, uY);

		m_MainTransform.SetPosition(glm::vec3(temp.x, temp.y, 0.02f));
	}

	std::tuple<int32_t, int32_t> Panel::GetCenter(Anchor relativeTo)
	{
		int xp = 0;
		int yp = 0;

		int height = m_RenderingCamera->GetHeight();
		int width = m_RenderingCamera->GetWidth();

		switch (m_Anchor) {
			case Anchor::TopLeft: { break; }
			case Anchor::TopRight: { xp = -width; break; }
			case Anchor::BottomLeft: {yp = -height;  break; }
			case Anchor::BottomRight: {xp = -width; yp = -height; break; }
			case Anchor::Center: {xp = -width / 2; yp = -height / 2; break; }
		}

		switch (relativeTo) {
			case Anchor::TopLeft: { break; }
			case Anchor::TopRight: { xp += width; break; }
			case Anchor::BottomLeft: {yp += height;  break; }
			case Anchor::BottomRight: {xp += width; yp += height; break; }
			case Anchor::Center: {xp += width / 2; yp += height / 2; break; }
		}

		auto ret = m_Center;

		std::get<0>(ret) -= xp;
		std::get<1>(ret) -= yp;

		return ret;
	}

	void Panel::SetCaptureCamera(const Ref<CameraBase>& capturingCamera)
	{

		m_CapturingCamera->GetOnResolutionChangeEvent().unsubscribe(m_OnCaptureResChangeCB);
		m_CapturingCamera = capturingCamera;
		m_CapturingCamera->GetOnResolutionChangeEvent().subscribe(m_OnCaptureResChangeCB);

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}


	}

	glm::vec2 Panel::GetScreenToClipSpacePosition(float x, float y)
	{
		float mx, my;


		float ac_ar = m_CapturingCamera->GetAspectRatio() / ((float)GetWidth() / (float)GetHeight());

		if (ac_ar >= 1.0f) {
			mx = 2.0f / m_Width;
			my = (-2.0f * ac_ar) / m_Height;
		}
		else {
			mx = 2.0f / (m_Width * ac_ar);
			my = -2.0f / m_Height;
		}

		float cx = -mx * std::get<0>(GetCenter(Anchor::TopLeft));
		float cy = -my * std::get<1>(GetCenter(Anchor::TopLeft));

		return { mx * x + cx,my * y + cy };
	}

	uint8_t Panel::GetDepth(float x, float y)
	{
		auto mp = GetScreenToClipSpacePosition(x, y);
		auto spec = m_CapturingCamera->GetFrameBuffer()->GetSpecification();
		return m_CapturingCamera->GetFrameBuffer()->GetDepthData((uint32_t)(spec.Width * 0.5f * (mp.x + 1.0f)), (uint32_t)(spec.Height * 0.5f * (mp.y + 1.0f)));
	}

	bool Panel::OnMainWindowSizeChangeHandler(int width, int height)
	{
		float  WS = ((float)m_Width / (float)m_RenderingCamera->GetWidth()) * m_RenderingCamera->GetAspectRatio();
		float HS = ((float)m_Height / (float)m_RenderingCamera->GetHeight());
		m_MainTransform.SetScale(glm::vec3(WS, HS, 1.0f));
		//m_MainTransform.SetPosition(glm::vec3(m_Position.x, m_Position.y, 0.0f));

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}

		SetPosition(std::get<0>(m_Center), std::get<1>(m_Center), Anchor::TopLeft);

		return PROPAGATE_EVENT;
	}

	void Panel::DragPanel(float x, float y)
	{
		auto mPos = GetScreenToClipSpacePosition(x, y);

		if (gwcEngine::Input::IsMouseButtonPressed(0) && std::fabs(mPos.x) <= 1.0f && std::fabs(mPos.y) <= 1.0f) {
			if (!isHeld) {
				isHeld = true;
				xHeld = (int)x;
				yHeld = (int)y;
				currentPos = GetCenter(Anchor::TopLeft);
			}

			int diffx = (int)x - xHeld;
			int diffy = (int)y - yHeld;

			SetPosition(std::get<0>(currentPos) + diffx, std::get<1>(currentPos) + diffy, gwcEngine::Anchor::TopLeft);
		}
		else {
			isHeld = false;
		}
	}

	bool Panel::OnMouseMovedHandler(float x, float y)
	{
		DragPanel(x, y);
		return PROPAGATE_EVENT;
	}

	void Panel::flush()
	{
		Renderer::SetActiveCamera(m_RenderingCamera);
		RenderCommand::SetViewport(0, 0, m_RenderingCamera->GetWidth(), m_RenderingCamera->GetHeight());

		//Draw panel clear colour
		gwcEngine::Renderer::Submit(m_RenderPlane.GetVertexArray(), m_DefaultShader, m_MainTransform.GetTransformMatrix());

		//Draw r
		m_CapturingCamera->GetFrameBuffer()->BindTexture();
		
		Renderer::Submit(m_RenderPlane.GetVertexArray(), m_UnlitTextureShader, m_RenderPlaneTransform.GetTransformMatrix());
	}

	bool Panel::OnCaptResChange(uint32_t x, uint32_t y)
	{
		SetSize(m_Width, m_Height);
		return PROPAGATE_EVENT;
	}
}