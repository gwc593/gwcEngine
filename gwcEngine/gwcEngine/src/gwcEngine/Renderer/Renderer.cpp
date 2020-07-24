#include"gepch.h"
#include"Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
namespace gwcEngine
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//TODO -shader data cube maps etc etc
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	//todo - camera polymorphic
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		//TODO - shader data cube maps etc etc
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::SetActiveCamera(const Ref<Camera>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::SetViewProjection(const glm::mat4& vp)
	{
		m_SceneData->ViewProjectionMatrix = vp;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		//Todo - should only update the view matrix to the shader once per frame, currently its being uploaded once per draw.
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		
		//upload entities transform
		shader->UploadUniformMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, Material& material, const glm::mat4& transform)
	{
		const Ref<Shader>& shader = material.GetShader();
		shader->Bind();
		//Todo - should only update the view matrix to the shader once per frame, currently its being uploaded once per draw.
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		//upload entities transform
		shader->UploadUniformMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}