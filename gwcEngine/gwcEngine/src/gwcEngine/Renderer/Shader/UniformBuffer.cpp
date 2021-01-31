#include "gepch.h"
#include "UniformBuffer.h"
#include"gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
namespace gwcEngine
{
	UniformBuffer* UniformBuffer::Create(const std::string& blockName)
	{

		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLUniformBuffer(blockName);


		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}
}
