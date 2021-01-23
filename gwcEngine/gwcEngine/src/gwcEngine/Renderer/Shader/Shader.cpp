#include"gepch.h"
#include"Shader.h"

#include "gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLUniforms/OpenGLUniforms.h"
namespace gwcEngine
{
	std::vector<std::weak_ptr<Shader>> Shader::m_Shaders;

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		Ref<Shader> ret = nullptr;
		switch (Renderer::GetAPI()) {
		case(RendererAPI::API::None):GE_CORE_ERROR("No rendering API selected"); break;
		case(RendererAPI::API::OpenGL):ret = CreateRef<OpenGLShader>(vertexSrc, fragmentSrc); break;
		}

		if (ret == nullptr) {
			GE_CORE_ERROR("Invalid rendering API selected");
			return ret;
		}

		m_Shaders.push_back(ret);
		return ret;
	}

	Ref<Shader> Shader::Create(const std::string& shaderPath)
	{
		Ref<Shader> ret = nullptr;
		switch (Renderer::GetAPI()) {
		case(RendererAPI::API::None):GE_CORE_ERROR("No rendering API selected"); break;
		case(RendererAPI::API::OpenGL):ret = CreateRef<OpenGLShader>(shaderPath); break;
		}

		if (ret == nullptr) {
			GE_CORE_ERROR("Invalid rendering API selected");
			return ret;
		}

		m_Shaders.push_back(ret);
		return ret;
	}


}