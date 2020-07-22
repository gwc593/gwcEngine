#include "gepch.h"*
#include "Panel.h"
#include "gwcEngine/Core/application.h"

namespace gwcEngine
{
	Panel::Panel(uint32_t width, uint32_t height, Ref<OrthographicCamera> camera) 
		:m_Width(width), m_Height(height),m_PanelCamera(camera)
	{
		//get window and panel geometry
		m_MainWindowWidth = Application::Get()->GetWindow().GetWidth();
		m_MainWindowHeight = Application::Get()->GetWindow().GetHeight();
		m_mainAspect = (float)m_MainWindowWidth / (float)m_MainWindowHeight;

		m_AspectRatio = (float)m_Width / (float)m_Height;
		m_PanelSpec.Height = m_Height;
		m_PanelSpec.Width = m_Width;
		m_FrameBuffer = FrameBuffer::Create(m_PanelSpec);

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

		m_DrawArea.SetVertexBuffer(verticesQuad, sizeof(verticesQuad), layout);

		//make mesh dynamic to allow for panel resizing isDynamic = true.
		m_DrawArea.SetIndexBuffer(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t), true);
#pragma endregion

		//setup callbacks
		c_OnMainWindowSizeChange = CreateRef<EventCallback<int, int>>();
		c_OnMainWindowSizeChange->SetCallback(BIND_EVENT_FN2(Panel::OnMainWindowSizeChange));
		Application::Get()->GetWindow().GetWindowResizeEvent().subscribe(c_OnMainWindowSizeChange);

		//setup panel shader
		m_UIShader = gwcEngine::Shader::Create("assets/Shaders/UnlitTexture.glsl");
		m_DefaultShader = gwcEngine::Shader::Create("assets/Shaders/PanelBackground.glsl");
	}

	bool Panel::OnSizeChange(uint32_t width, uint32_t height)
	{
		return PROPAGATE_EVENT;
	}

	bool Panel::OnMainWindowSizeChange(int width, int height)
	{
		m_MainWindowWidth = width;
		m_MainWindowHeight = height;
		m_mainAspect = (float)m_MainWindowWidth / (float)m_MainWindowHeight;
		return PROPAGATE_EVENT;
	}

	void Panel::Bind()
	{
		m_FrameBuffer->Bind();
	}

	void Panel::Unbind()
	{
		m_FrameBuffer->Unbind();
	}

	void Panel::flush()
	{
		Renderer::SetActiveCamera(m_PanelCamera);
		RenderCommand::Clear();
		Renderer::Submit(m_DrawArea.GetVertexArray(), m_DefaultShader, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f)));
		
		m_FrameBuffer->BindTexture();
		//Renderer::Submit(m_DrawArea.GetVertexArray(), m_UIShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0, m_AspectRatio/m_mainAspect,1.0f)));
	}

}