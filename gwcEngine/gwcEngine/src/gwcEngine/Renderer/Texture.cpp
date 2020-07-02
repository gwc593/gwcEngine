#include "gepch.h"
#include "Texture.h"
#include "gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLTexture.h"

namespace gwcEngine 
{

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "No rendering API selected...");
			return nullptr;

		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);


		}

		GE_CORE_ASSERT(false, "Invalid Renderer API...");
		return nullptr;
	}
}