#include"gepch.h"
#include"Buffer.h"

#include"Renderer.h"

#include"platform/OpenGL/OpenGLBuffer.h"

//TODO - gwc: ifdef include directx implimentation header..
namespace gwcEngine
{
	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(verticies, size);


		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indicies, size);


		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}
}
