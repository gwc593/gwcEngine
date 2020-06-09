#include<gwcEngine.h>

#include<glm/gtc/matrix_transform.hpp>
class Target : public gwcEngine::Layer
{
public:
	Target()
		:Layer("Example"), 
		m_Camera(-1.6f,1.6f,-0.9f,0.9f), //orthographic camera initializer
		//m_Camera(70.0f,1.78f,0.0f,1000.0f), //perspective camera initializer
		m_squarePosition(glm::vec3(0.0f))
	{
		/// first triangle
		m_VertexArray.reset(gwcEngine::VertexArray::Create());

		//triagle vertex data
		float vertices[3 * 7] = {
			// -----Position-----  ------Colour-------
				-0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0,
				0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0, 1.0,
				0.0f, 0.5f, 0.0f,   0.0, 0.0, 1.0, 1.0
		};
		std::shared_ptr<gwcEngine::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(gwcEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"},
			{gwcEngine::ShaderDataType::Float4, "a_Colour"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0,1,2 };

		std::shared_ptr<gwcEngine::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(gwcEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

#pragma region Square
		m_SquareVertexArray.reset(gwcEngine::VertexArray::Create());

		float SquareVertices[4 * 7] = {
			// -----Position-----  ------Colour-------
				-0.75f, 0.75f, 0.0f, 0.0, 0.0, 0.0, 1.0,
				-0.75f, -0.75f, 0.0f,  0.0, 0.0, 0.0, 1.0,
				0.75f, -0.75f, 0.0f,   0.0, 0.0, 0.0, 1.0,
				0.75f, 0.75f, 0.0f,   0.0, 0.0, 0.0, 1.0
		};
		std::shared_ptr<gwcEngine::VertexBuffer> SquareVB;
		SquareVB.reset(gwcEngine::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));



		SquareVB->SetLayout(layout);

		m_SquareVertexArray->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0,1,3,
									3,1,2 };

		std::shared_ptr<gwcEngine::IndexBuffer> SquareIB;
		SquareIB.reset(gwcEngine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(SquareIB);

#pragma endregion




		//create a basic shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;
			
			void main()
			{
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position,1.0);
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

		m_Shader.reset(new gwcEngine::Shader(vertexSrc, fragmentSrc));
	}

	void CameraController()
	{
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = m_Camera.GetPostion();
			//Todo, move camera space not world space
			m_Camera.SetPosition({ pos.x, pos.y += 1.0 * gwcEngine::Time::GetDeltaTime(), pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x -= 1.0 * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y -= 1.0 * gwcEngine::Time::GetDeltaTime(), pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x += 1.0 * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}
		/*
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			m_camerRot -= 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation(glm::vec3(0, m_camerRot, 0));
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			m_camerRot += 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation(glm::vec3(0, m_camerRot, 0));
		}
		*/
		
	}

	void SquareController()
	{
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::I)) {
			m_squarePosition.y += 1.0 * gwcEngine::Time::GetDeltaTime();
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::J)) {
			m_squarePosition.x += -1.0 * gwcEngine::Time::GetDeltaTime();
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::K)) {
			m_squarePosition.y += -1.0 * gwcEngine::Time::GetDeltaTime();
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::L)) {
			m_squarePosition.x += 1.0 * gwcEngine::Time::GetDeltaTime();
		}
		
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::O)) {
			m_squareRotation -= 20.0 * gwcEngine::Time::GetDeltaTime();
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::U)) {
			m_squareRotation += 20.0 * gwcEngine::Time::GetDeltaTime();
		}
		
	}


	void OnUpdate() override
	{
		CameraController();
		SquareController();

		GE_TRACE(m_camerRot);
		gwcEngine::RenderCommand::Clear();

		gwcEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_squarePosition) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_squareRotation), glm::vec3(0, 1, 0));
		gwcEngine::Renderer::Submit(m_SquareVertexArray, m_Shader, transform);
		gwcEngine::Renderer::Submit(m_VertexArray, m_Shader);

		gwcEngine::Renderer::EndScene();
	}



	void OnEvent(gwcEngine::Event& event) override
	{

	}

private:
	float dx = 0;
	std::shared_ptr<gwcEngine::VertexArray> m_VertexArray;
	std::shared_ptr<gwcEngine::Shader> m_Shader;

	std::shared_ptr<gwcEngine::VertexArray> m_SquareVertexArray;
	//gwcEngine::OrthographicCamera m_Camera;
	gwcEngine::PerspectiveCamera m_Camera;

	glm::vec3 m_squarePosition;
	float m_squareRotation = 0.0f;
	float m_camerRot = 0.0f;
};




//client side implementation of gwcEngine instance
class Sandbox : public gwcEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new Target());
	}

	~Sandbox()
	{

	}

};

//required by EntryPoint.h
gwcEngine::Application* gwcEngine::CreateApplication()
{
	return new Sandbox();
}