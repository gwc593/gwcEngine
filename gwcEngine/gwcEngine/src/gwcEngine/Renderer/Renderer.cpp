#include"gepch.h"
#include"Renderer.h"

namespace gwcEngine
{
	void Renderer::BeginScene()
	{
		//TODO - view space stuff here
		//shader data cube maps etc etc
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}