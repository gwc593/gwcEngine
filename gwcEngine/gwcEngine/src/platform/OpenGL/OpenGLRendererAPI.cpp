#include"gepch.h"
#include"OpenGLRendererAPI.h"

#include<glad/glad.h>
namespace gwcEngine
{
	void OpenGLRendererAPI::Clear()
	{
		glClearColor(0.15, 0.15, 0.15, 1);
	}

	void OpenGLRendererAPI::SetClearColour()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}