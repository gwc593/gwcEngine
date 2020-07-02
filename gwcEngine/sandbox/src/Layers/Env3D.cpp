#include"Env3D.h"

glm::vec4 redColour = { 1.0f,0.0f,0.0f, 1.0f };
glm::vec4 greenColour = { 0.0f,1.0f,0.0f, 1.0f };
glm::vec4 blueColour = { 0.0f,0.0f,1.0f, 1.0f };

	Env3D::Env3D()
		:Layer("3DEnv"),
		m_PCamera(gwcEngine::CreateRef<gwcEngine::PerspectiveCamera>(58.0, 1.78f, 0.1f, 300.0f)), //perspective camera initializer
		m_UICamera(gwcEngine::CreateRef<gwcEngine::OrthographicCamera>(-1.6,1.6,-0.9,0.9)) //perspective camera initializer
	{

	}

	void Env3D::OnAttach()
	{
		//temp framebuffer spec
		gwcEngine::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = gwcEngine::FrameBuffer::Create(fbSpec);

		//temp texture.
		m_castleTexture = gwcEngine::Texture2D::Create("assets/castle.png");

		//subscribe frameBuffer to windowSizeChange
		auto& resizeEvent = gwcEngine::Application::Get()->GetWindow().GetWindowResizeEvent();
		resizeEvent.subscribe((BIND_EVENT_FNO2(gwcEngine::FrameBuffer::Resize, *m_FrameBuffer)));

//entity and components and systems
		//create entity renderer
		gwcEngine::Ref<gwcEngine::RendererECS> rendSys = gwcEngine::CreateRef<gwcEngine::RendererECS> ("3dRenderer",m_ECS_Manager);
		//regiseter entity renderer
		m_ECS_Manager.RegisterSystem(std::dynamic_pointer_cast<gwcEngine::ISystem>(rendSys));

//make a cube entity
		m_CubeEntity = m_ECS_Manager.CreateEntity("Cube");
		auto& triMesh = m_ECS_Manager.AddComponent<gwcEngine::Mesh>(m_CubeEntity);
		auto& transform = m_ECS_Manager.AddComponent<gwcEngine::Transform>(m_CubeEntity);
		auto& t_Mat = m_ECS_Manager.AddComponent<gwcEngine::Material>(m_CubeEntity);
		//TODO add camera reference.

#pragma region CubeMeshData
		gwcEngine::BufferLayout layoutUnlitShader = {
			{gwcEngine::ShaderDataType::Float3, "a_Position"} };

		float verticesCube[8 * 3] = {
			// -----Position-----// -- normal-------- 
				0.5f, 0.5f, 0.5f,
			   -0.5f, 0.5f, 0.5f,
			   -0.5f,-0.5f, 0.5f,
				0.5f,-0.5f, 0.5f,
				0.5f, 0.5f,-0.5f,
			   -0.5f, 0.5f,-0.5f,
			   -0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f
		};
		                   //f   t   v
		uint32_t indicesCube[6 * 2 * 3] = {
			0,1,2,
			0,2,3,
			4,1,0,
			4,5,1,
			4,5,6,
			4,6,7,
			1,5,6,
			1,6,2,
			0,3,7,
			4,0,7,
			7,6,2,
			7,2,3 };

#pragma endregion

#pragma region QuadMeshData
		gwcEngine::BufferLayout layoutTextureShader = {
				{gwcEngine::ShaderDataType::Float3, "a_Position"},
				{gwcEngine::ShaderDataType::Float2, "a_TexCoord"}
				};

		float verticesQuad[4 * 5] = {
			// -----Position-----// -- Texture coord-------- 
				1.6f, 0.9f, 0.0f,      1.0f, 1.0f,
				1.6f,-0.9f, 0.0f,      1.0f, 0.0f,
			   -1.6f,-0.9f, 0.0f,      0.0f, 0.0f,
			   -1.6f, 0.9f, 0.0f,      0.0f, 1.0f
		};
		               //f   t   v
		uint32_t indicesQuad[1 * 2 * 3] = {
			0,1,2,
			0,2,3,
		};

		QuadMesh.SetVertexBuffer(verticesQuad, sizeof(verticesQuad), layoutTextureShader);
		QuadMesh.SetIndexBuffer(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t));

#pragma endregion
		triMesh.SetVertexBuffer(verticesCube, sizeof(verticesCube), layoutUnlitShader);
		triMesh.SetIndexBuffer(indicesCube, sizeof(indicesCube) / sizeof(uint32_t));

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


#pragma region unlitTextureShaderSrc
		//create a basic shader
		std::string unlitTextureVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec2 v_TexCoord;
			
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
			}
		)";

		std::string unlitTextureFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
#pragma endregion

		m_UnlitColourShader.reset(gwcEngine::Shader::Create(unlitColourvertexSrc, unlitColourfragmentSrc));
		m_UnlitTexturedShader.reset(gwcEngine::Shader::Create(unlitTextureVertexSrc, unlitTextureFragmentSrc));

		m_UnlitTexturedShader->Bind();
		m_UnlitTexturedShader->UploadUniformInt("u_Texture", 0);//slot 0) //

		t_Mat.SetShader(m_UnlitColourShader);

	}

	void Env3D::CameraController(gwcEngine::Ref<gwcEngine::Camera> camera)
	{
		auto pCamera = std::dynamic_pointer_cast<gwcEngine::PerspectiveCamera>(m_PCamera);
		
		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::W)) {
			glm::vec3 pos = camera->GetPostion();
			//Todo, move camera space not world space
			camera->SetPosition({ pos.x, pos.y , pos.z -= 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::A)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x -= 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::S)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y, pos.z += 1.0f * gwcEngine::Time::GetDeltaTime() });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::D)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x += 1.0f * gwcEngine::Time::GetDeltaTime(), pos.y , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::E)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y += 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

		if (gwcEngine::Input::IsKeyPressed((int)gwcEngine::KeyCode::Q)) {
			glm::vec3 pos = camera->GetPostion();
			camera->SetPosition({ pos.x, pos.y -= 1.0f * gwcEngine::Time::GetDeltaTime() , pos.z });
		}

	}

	void Env3D::OnUpdate()
	{
		GE_TRACE("fps = {0}", 1.0f / gwcEngine::Time::GetDeltaTime());
		//Make the material change colour with time
		float t = gwcEngine::Time::GetTime();
		float r = 0.5f * (glm::sin(t + 45.0f) + 1.0f);
		float g = 0.5f * (glm::sin(0.333f * t) + 1.0f);
		float b = 0.5f * (glm::sin(2.0f * t) + 1.0f);
		m_ECS_Manager.GetComponent<gwcEngine::Material>(m_CubeEntity).SetValue("u_Colour", glm::vec4(r, g, b, 1.0f));



//Move and rotate cube
		auto& cubeTransform = m_ECS_Manager.GetComponent<gwcEngine::Transform>(m_CubeEntity);
		auto xPos = cubeTransform.GetPosition();
		xPos.x =(2.0f* r -1.0f);
		cubeTransform.SetPosition(glm::vec3(r-1, g-1, b-1)*2.0f);
		cubeTransform.SetRotation(glm::vec3(r, g, b)*8.0f);
	
//move perspective Camera
		CameraController(m_PCamera);

//Draw 3d Environment renderPass
		m_FrameBuffer->Bind();
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_PCamera);
		m_ECS_Manager.OnUpdate(gwcEngine::Time::GetDeltaTime());
		m_FrameBuffer->Unbind();

//Draw 2D orthographic UI layer
		gwcEngine::RenderCommand::Clear();
		gwcEngine::Renderer::SetActiveCamera(m_UICamera);
		m_FrameBuffer->BindTexture();
		gwcEngine::Renderer::Submit(QuadMesh.GetVertexArray(), m_UnlitTexturedShader);
		gwcEngine::Renderer::EndScene();
		
	}
