#include"gepch.h"
#include"Renderer.h"
#include "gwcEngine/Renderer/Shader/Shader.h"
#include "gwcEngine/Components/Cameras/Camera.h"
namespace gwcEngine
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene()
	{
		//TODO -shader data cube maps etc etc


	}

	void Renderer::SetActiveCamera(const Ref<CameraBase>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
		for (auto shaderPTR : Shader::GetShaders()) {
			auto shader = shaderPTR.lock();
			auto trans = camera->GetTransform();
			if(trans)
				shader->UploadUniformVec3("u_EyeDirection", trans->Forward());
		}

	}

	void Renderer::SetViewProjection(const glm::mat4& vp)
	{
		m_SceneData->ViewProjectionMatrix = vp;
	}

	void Renderer::EndScene()
	{
		PROFILE_FUNCTION();
		Application::Get()->GetWindow().SwapBuffers();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, RendType rType)
	{
		shader->Bind();
		//Todo - should only update the view matrix to the shader once per frame, currently its being uploaded once per draw.
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		
		//upload entities transform
		shader->UploadUniformMat4("u_Transform", transform);


		vertexArray->Bind();
		switch (rType) {
		case gwcEngine::RendType::none:
			GE_CORE_ASSERT(false, "No Render type selected");
			break;
		case gwcEngine::RendType::lines:
			RenderCommand::DrawLinesIndexed(vertexArray);
			break;
		case gwcEngine::RendType::triangles:
			RenderCommand::DrawTrisIndexed(vertexArray);
			break;
		default:
			GE_CORE_ASSERT(false, "Unsupported Render type selected");
			break;
		}
		
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform, RendType rType)
	{
		const Ref<Shader>& shader = material->GetShader();
		shader->Bind();
		//Todo - should only update the view matrix to the shader once per frame, currently its being uploaded once per draw.
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		//upload entities transform
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();

		switch (rType) {
		case gwcEngine::RendType::none:
			GE_CORE_ASSERT(false, "No Render type selected");
			break;
		case gwcEngine::RendType::lines:
			RenderCommand::DrawLinesIndexed(vertexArray);
			break;
		case gwcEngine::RendType::triangles:
			RenderCommand::DrawTrisIndexed(vertexArray);
			break;
		default:
			GE_CORE_ASSERT(false, "Unsupported Render type selected");
			break;
		}

	}
}