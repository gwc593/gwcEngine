#include "gepch.h"
#include "FrameBuffer.h"
#include "gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLFrameBuffer.h"
namespace gwcEngine
{
	


	gwcEngine::Ref<gwcEngine::FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);
		}

		GE_CORE_ASSERT(false, "Invalid Rendering API selected");
	}

}