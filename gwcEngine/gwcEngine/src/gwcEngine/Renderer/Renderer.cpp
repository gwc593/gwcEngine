#include"gepch.h"
#include"Renderer.h"

namespace gwcEngine
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		//TODO - view space stuff here
		//shader data cube maps etc etc
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		//TODO - view space stuff here
		//shader data cube maps etc etc
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4 transform)
	{
		shader->Bind();
		//Todo - should only update the view matrix to the shader once per frame, currently its being uploaded once per draw.
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		
		//upload entities transform
		shader->UploadUniformMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}