#include"gepch.h"
#include"VertexArray.h"
#include"gwcEngine/Renderer/Renderer.h"

#include"platform/OpenGL/OpenGLVertexArray.h"
namespace gwcEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}
}