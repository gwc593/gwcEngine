#include"gepch.h"
#include"Shader.h"

#include"Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
namespace gwcEngine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case(RendererAPI::API::None):GE_CORE_ERROR("No rendering API selected");
		case(RendererAPI::API::OpenGL):return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GE_CORE_ERROR("Invalid rendering API selected");
		return nullptr;
	}

}