#include"World.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	World::World()
		:Layer("3DWorld"),
		m_Camera(70.0f, 1.78f, 0.8f, 300.0f) //perspective camera initializer
	{
	
		//entity and components
		triangleEntity = m_EntityManager.CreateEntity("TestEntityA");

		auto triMesh = m_ComponentManager.AddComponent<gwcEngine::Mesh>(triangleEntity);
		m_ComponentManager.AddComponent<gwcEngine::Transform>(triangleEntity);
		auto t_mat = m_ComponentManager.AddComponent<gwcEngine::Material>(triangleEntity);

		triangleEntity->Destroy();

#pragma region TriangleMeshData
		gwcEngine::BufferLayout layout = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"}};

		float vertices[3 * 3] = {
			// -----Position-----  
				-0.5f, 0.0f, 0.0f,
				0.5f, 0.0, 0.0f,
				0.0f, 1.0f, 0.0f
		};

		uint32_t indices[3] = { 0,1,2 };

#pragma endregion


		triMesh.SetVertexBuffer(vertices, sizeof(vertices), layout);
		triMesh.SetIndexBuffer(indices, 3);

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

		m_UnlitColourShader.reset(gwcEngine::Shader::Create(unlitColourvertexSrc, unlitColourfragmentSrc));
		m_UnlitColour.SetShader(m_UnlitColourShader);
	}

	void World::CameraController()
	{
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = m_Camera.GetPostion();
			//Todo, move camera space not world space
			m_Camera.SetPosition({ pos.x, pos.y , pos.z -= 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x -= 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x, pos.y, pos.z += 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = m_Camera.GetPostion();
			m_Camera.SetPosition({ pos.x += 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			m_camerRot -= 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation({ 0, m_camerRot, 0 });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			m_camerRot += 1.0f * gwcEngine::Time::GetDeltaTime();
			m_Camera.SetRotation({ 0, m_camerRot, 0 });
		}

	}
	bool set = false;

	void World::OnUpdate()
	{
		
		float t = gwcEngine::Time::GetTime();
		float r = 0.5f * (glm::sin(t + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * t) + 1.0f);
		float b = 0.5f * (glm::sin(2.0f * t) + 1.0f);

	
		m_UnlitColour.SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));
		CameraController();

		gwcEngine::RenderCommand::Clear();


		gwcEngine::Renderer::BeginScene(m_Camera);

		gwcEngine::Renderer::Submit(m_ComponentManager.GetComponent<gwcEngine::Mesh>(triangleEntity).GetVertexArray(), m_UnlitColourShader);
		//gwcEngine::Renderer::Submit(test1.m_CompRef->GetVertexArray(), m_UnlitColourShader);

		gwcEngine::Renderer::EndScene();
	}

	bool World::onClicked(const gwcEngine::MouseButtonPressedEvent& e)
	{
		if (e.GetButton() == (int)gwcEngine::MouseCode::Button0) {
			GE_TRACE("you clicked the fancy triangle");
			return true;
		}
		return false;
	}

	bool World::onSpaceBar(const gwcEngine::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == (int)gwcEngine::KeyCode::Space) {
			gwcEngine::RenderCommand::SetVsync(!gwcEngine::RenderCommand::IsVsync());
			return true;
		}
		return false;
	}

	bool World::OnEvent(gwcEngine::Event& event)
	{
		
		gwcEngine::EventDispatcher dp(event);
		event.Handled |= dp.Dispatch<gwcEngine::MouseButtonPressedEvent>(BIND_EVENT_FN(World::onClicked));
		event.Handled |= dp.Dispatch<gwcEngine::KeyPressedEvent>(BIND_EVENT_FN(World::onSpaceBar));

		//GE_TRACE(event.ToString());
		return event.Handled;
	}

