#include "gepch.h"*
#include "Panel.h"
#include "gwcEngine/Core/application.h"
#include "gwcEngine/Core/Input.h"

namespace gwcEngine
{
	Panel::Panel(uint32_t width, uint32_t height, Ref<Camera> renderingCamera, Ref<Camera> capturingCamera)
		:m_Width(width), m_Height(height),m_RenderingCamera(renderingCamera), m_CapturingCamera(capturingCamera)
	{
		if (capturingCamera == nullptr)
			m_CapturingCamera = m_RenderingCamera;

		//get window and panel geometry

		m_AspectRatio = (float)m_Width / (float)m_Height;
		
		//create unit quad to render draw.
#pragma region QuadMeshData

		gwcEngine::BufferLayout layout = {
				{gwcEngine::ShaderDataType::Float3, "a_Position"},
				{gwcEngine::ShaderDataType::Float2, "a_TexCoord"}
		};

		float left = -0.5f;
		float right = 0.5f;
		float bottom = -0.5f ;
		float top = 0.5f;

			float verticesQuad[4 * 5] = {
			// ----------Position--------------// -- Texture coordinates----- 
				right, top,    0.0f,      1.0f, 1.0f,
				right, bottom, 0.0f,      1.0f, 0.0f,
			    left,  bottom, 0.0f,      0.0f, 0.0f,
			    left,  top,    0.0f,      0.0f, 1.0f
			};

		//f   t   v
		uint32_t indicesQuad[1 * 2 * 3] = {
			0,1,2,
			0,2,3,
		};

		m_RenderPlane.SetVertexBuffer(verticesQuad, sizeof(verticesQuad), layout);

		//make mesh dynamic to allow for panel resizing isDynamic = true.
		m_RenderPlane.SetIndexBuffer(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t), true);
#pragma endregion

		//setup callbacks
		c_OnMainWindowSizeChange = CreateRef<EventCallback<int, int>>();
		c_OnMainWindowSizeChange->SetCallback(BIND_EVENT_FN2(Panel::OnMainWindowSizeChangeHandler));
		Application::Get()->GetWindow().GetWindowResizeEvent().subscribe(c_OnMainWindowSizeChange);

		c_OnMouseMoved = CreateRef<EventCallback<float, float>>();
		//c_OnMouseMoved->SetCallback([&](float& x, float& y) {GE_TRACE("{0}, {1}",x,y); return false; });
		c_OnMouseMoved->SetCallback(BIND_EVENT_FN2(Panel::OnMouseMovedHandler));
		Input::GetMouseMovedEvent().subscribe(c_OnMouseMoved);

		//setup panel shader
		m_UnlitTextureShader = gwcEngine::Shader::Create("assets/Shaders/UnlitTexture.glsl");
		m_DefaultShader = gwcEngine::Shader::Create("assets/Shaders/PanelBackground.glsl");

		m_Position = glm::vec2(0.0f);
		m_RenderPlaneTransform.SetPosition(glm::vec3(m_Position.x, m_Position.y, 0.2f));
		
		m_RenderPlaneTransform.SetParent(m_MainTransform);


		float  WS = ((float)m_Width / (float)m_RenderingCamera->GetWidth()) * m_RenderingCamera->GetAspectRatio();
		float HS = ((float)m_Height / (float)m_RenderingCamera->GetHeight());
		m_MainTransform.SetScale(glm::vec3(WS, HS, 1.0f));
		m_MainTransform.SetPosition(glm::vec3(m_Position.x, m_Position.y, -0.2f));

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}
	}

	void Panel::SetSize(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
		m_AspectRatio = width / height;
	}

	void Panel::SetPosition(int x, int y, Anchor relativeTo)
	{
		m_Position = m_RenderingCamera->ScreenToWorld(x, y, Application::Get()->GetWindow());
		m_RenderPlaneTransform.SetPosition(glm::vec3(m_Position.x, m_Position.y, 0.02f));
	}

	bool Panel::OnMainWindowSizeChangeHandler(int width, int height)
	{
		float  WS = ((float)m_Width / (float)m_RenderingCamera->GetWidth()) * m_RenderingCamera->GetAspectRatio();
		float HS = ((float)m_Height / (float)m_RenderingCamera->GetHeight());
		m_MainTransform.SetScale(glm::vec3(WS, HS, 1.0f));
		m_MainTransform.SetPosition(glm::vec3(m_Position.x, m_Position.y, 0.0f));

		if (m_AspectRatio > m_CapturingCamera->GetAspectRatio()) {

			m_RenderPlaneTransform.SetScale(glm::vec3(m_CapturingCamera->GetAspectRatio() / m_AspectRatio, 1.0f, 1.0f));
		}
		else {
			m_RenderPlaneTransform.SetScale(glm::vec3(1.0f, m_AspectRatio / m_CapturingCamera->GetAspectRatio(), 1.0f));
		}

		return PROPAGATE_EVENT;
	}
	bool Panel::OnMouseMovedHandler(float x, float y)
	{

		auto res = m_RenderingCamera->ScreenToWorld(x, y, Application::Get()->GetWindow());
		GE_TRACE("{0}, {1}", res.x, res.y);
		return false;
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
}