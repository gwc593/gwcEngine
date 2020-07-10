#include"gepch.h"
#include"Shader.h"

#include "gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLUniforms/OpenGLUniforms.h"
namespace gwcEngine
{
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case(RendererAPI::API::None):GE_CORE_ERROR("No rendering API selected");
		case(RendererAPI::API::OpenGL):return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		GE_CORE_ERROR("Invalid rendering API selected");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& shaderPath)
	{
		switch (Renderer::GetAPI()) {
		case(RendererAPI::API::None):GE_CORE_ERROR("No rendering API selected");
		case(RendererAPI::API::OpenGL):return CreateRef<OpenGLShader>(shaderPath);
		}

		GE_CORE_ERROR("Invalid rendering API selected");
		return nullptr;
	}


}