#include "gepch.h"
#include "IndexBuffer.h"

#include"gwcEngine/Renderer/Renderer.h"
#include"platform/OpenGL/OpenGLIndexBuffer.h"
namespace gwcEngine
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t count, bool isDynamic)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indicies, count, isDynamic);


		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}
}
