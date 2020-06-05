#include "gepch.h"

#include "Application.h"
#include "Input.h"
#include<glad/glad.h>

namespace gwcEngine {

	Application*  Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float1: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "unsupported ShaderDataType");
		return 0;
	}

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());	
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		s_Instance = this;

		//Todo - develope front end components or integrte IMGUI_LAYER.... maybe? i dont want to though
		
		/// first triangle
		m_VertexArray.reset(VertexArray::Create());

		//triagle vertex data
		float vertices[3 * 7] = {
		// -----Position-----  ------Colour-------
			-0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0,
			0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0, 1.0,
			0.0f, 0.5f, 0.0f,   0.0, 0.0, 1.0, 1.0
		};		
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Colour"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0,1,2 };

		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

#pragma region Square
		m_SquareVertexArray.reset(VertexArray::Create());

		float SquareVertices[4 * 7] = {
			// -----Position-----  ------Colour-------
				-0.75f, 0.75f, 0.0f, 0.0, 0.0, 0.0, 1.0,
				-0.75f, -0.75f, 0.0f,  0.0, 0.0, 0.0, 1.0,
				0.75f, -0.75f, 0.0f,   0.0, 0.0, 0.0, 1.0,
				0.75f, 0.75f, 0.0f,   0.0, 0.0, 0.0, 1.0
		};
		std::shared_ptr<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));



		SquareVB->SetLayout(layout);

		m_SquareVertexArray->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0,1,3,
									3,1,2};

		std::shared_ptr<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(SquareIB);

#pragma endregion




		//create a basic shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec3 v_Position;
			out vec4 v_Colour;
			
			void main()
			{
				gl_Position = vec4(a_Position,1.0);
				v_Position = a_Position;
				v_Colour = a_Colour;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Colour;
			void main()
			{
				color = v_Colour;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));

	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			
			m_Shader->Bind();

			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);

		//display to consol the event.
		//GE_CORE_TRACE("{0}", e.ToString());

		//if the event 'e' is the same type as the template used for Dispatch, then dispatch it using the function bound by the bind event function.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//pass event to layers
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}


}