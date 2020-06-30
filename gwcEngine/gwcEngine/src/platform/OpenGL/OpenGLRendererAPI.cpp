#include"gepch.h"
#include"OpenGLRendererAPI.h"
#include"gwcEngine/Core/application.h"
#include<glad/glad.h>
namespace gwcEngine
{
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetVSync(bool state)
	{
		Application::Get()->GetWindow().SetVsync(state);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	bool OpenGLRendererAPI::IsVsync()
	{
		return Application::Get()->GetWindow().IsVSync();
	}

}