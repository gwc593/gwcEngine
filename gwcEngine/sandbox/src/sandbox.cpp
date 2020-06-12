#include<gwcEngine.h>

//todo gwc - provide abstract methods to upload uniforms to the shader... this is a hack below
#include "platform/OpenGL/OpenGLShader.h"

#include<glm/gtc/matrix_transform.hpp>

//TODO TOMORROW - make this a part of every layer.
//gwcEngine::ECSManager layerECSManager;
//gwcEngine::Entity& triangleEnt = layerECSManager.AddEntity();
//gwcEngine::Entity& SquareEnt = layerECSManager.AddEntity();

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };



class Target : public gwcEngine::Layer
{
public:
	Target()
		:Layer("Example"),
		//m_Camera(-1.6f,1.6f,-0.9f,0.9f), //orthographic camera initializer
		m_Camera(70.0f, 1.78f, 0.8f, 300.0f), //perspective camera initializer
		m_squarePosition(glm::vec3(0.0f))
	{
		

		gwcEngine::Entity& triangleEnt = m_LayerManager.AddEntity();
		gwcEngine::Entity& SquareEnt = m_LayerManager.AddEntity();
		triangleEnt.AddComponent<gwcEngine::Mesh>();
		SquareEnt.AddComponent<gwcEngine::Mesh>();


#pragma region TriangleMeshData
		float vertices[3 * 3] = {
			// -----Position-----  ------Colour-------
				-0.5f, 0.0f, 0.0f,
				0.5f, 0.0, 0.0f,
				0.0f, 1.0f, 0.0f
		};


		gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"}
		};


		uint32_t indices[3] = { 0,1,2 };

#pragma endregion

		triangleEnt.GetComponent<gwcEngine::Mesh>().SetVertexBuffer(vertices, sizeof(vertices), layout);
		triangleEnt.GetComponent<gwcEngine::Mesh>().SetIndexBuffer(indices, 3);

#pragma region SquareMeshData
		float SquareVertices[4 * 3] = {
			// -----Position-----  ------Colour-------
				-0.75f, 0.75f, 0.0f,
				-0.75f, -0.75f, 0.0f,
				0.75f, -0.75f, 0.0f,
				0.75f, 0.75f, 0.0f
		};

		gwcEngine::BufferLayout layout2 = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"}
		};

		uint32_t SquareIndices[6] = { 0,1,3,
									3,1,2 };

		
#pragma endregion

		SquareEnt.GetComponent<gwcEngine::Mesh>().SetVertexBuffer(SquareVertices, sizeof(SquareVertices), layout2);
		SquareEnt.GetComponent<gwcEngine::Mesh>().SetIndexBuffer(SquareIndices, 6);

#pragma region unlitFlatShaderSrc
		//create a basic shader
		std::string unlitColourvertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
				v_Position = a_Position;
			}
		)";

		std::string unlitColourfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			uniform vec4 u_Colour;

			in vec3 v_Position;

			void main()
			{
				color = u_Colour;
			}
		)";

#pragma endregion

		m_UnlitColour.reset(gwcEngine::Shader::Create(unlitColourvertexSrc, unlitColourfragmentSrc));
		sqr = std::move(SquareEnt);
		tri = std::move(triangleEnt);
	}

	void CameraController()
	{
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = m_Camera.GetPostion();
			//Todo, move camera space not world space
			m_Camera.SetPosition({ pos.x, pos.y , pos.z -= 1.0 * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x -= 1.0 * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y, pos.z += 1.0 * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x += 1.0 * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			m_camerRot -= 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation(glm::vec3(0, m_camerRot, 0));
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			m_camerRot += 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation(glm::vec3(0, m_camerRot, 0));
		}

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


	float scale = 0.1f;
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));


	void OnUpdate() override
	{
		//GetComponentManager().OnUpdate();

		CameraController();
		SquareController();


		gwcEngine::RenderCommand::Clear();

		
		gwcEngine::Renderer::BeginScene(m_Camera);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * (scale + 0.5 * scale), y * (scale + 0.5 * scale), 0.0f);
				pos += m_squarePosition;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
					* glm::rotate(glm::mat4(1.0f), glm::radians(m_squareRotation), glm::vec3(0, 1, 0))
					* scaleMat;
				if ((x + y) % 2 == 0)
					m_UnlitColour->UploadUniformVec4("u_Colour", blueColour);
				else
					m_UnlitColour->UploadUniformVec4("u_Colour", greenColour);

				gwcEngine::Renderer::Submit(sqr.GetComponent<gwcEngine::Mesh>().GetVertexArray(), m_UnlitColour, transform);
			}
		}

		m_UnlitColour->UploadUniformVec4("u_Colour", redColour);
		gwcEngine::Renderer::Submit(tri.GetComponent<gwcEngine::Mesh>().GetVertexArray(), m_UnlitColour);

		gwcEngine::Renderer::EndScene();
	}

	bool onClicked(const gwcEngine::MouseButtonPressedEvent& e)
	{
		if (e.GetButton() == (int)gwcEngine::MouseCode::Button0)
			GE_TRACE("you clicked the fancy triangle");
		return true;
	}

	void OnEvent(gwcEngine::Event& event) override
	{
		gwcEngine::EventDispatcher dp(event);

		dp.Dispatch<gwcEngine::MouseButtonPressedEvent>(BIND_EVENT_FN(Target::onClicked));
	}

private:
	gwcEngine::PerspectiveCamera m_Camera;

	std::shared_ptr<gwcEngine::Shader> m_UnlitColour;

	glm::vec3 m_squarePosition;
	float m_squareRotation = 0.0f;
	float m_camerRot = 0.0f;

	gwcEngine::Entity tri;
	gwcEngine::Entity sqr;

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