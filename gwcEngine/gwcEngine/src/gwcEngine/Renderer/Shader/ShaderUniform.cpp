#include"gepch.h"
#include "ShaderUniform.h"
#include "gwcEngine/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLUniforms/OpenGLUniforms.h"
namespace gwcEngine
{


	ShaderUniform* ShaderUniform::Create(const std::string& name, const ShaderDataType& type, Shader* shader)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None: GE_CORE_ERROR("No rendering API selected"); break;
		case RendererAPI::API::OpenGL: 
		{
			switch (type) {
			case ShaderDataType::None: break;
			case ShaderDataType::Float1:break;
			case ShaderDataType::Float2:break;
			case ShaderDataType::Float3:break;
			case ShaderDataType::Float4:return new OpenGLUniformVec4(name, shader);
			case ShaderDataType::Mat3:break;
			case ShaderDataType::Mat4: return new OpenGLUniformMat4(name, shader);
			case ShaderDataType::Int:break;
			case ShaderDataType::Int2:break;
			case ShaderDataType::Int3:break;
			case ShaderDataType::Int4:break;
			case ShaderDataType::Bool:break;
			}
			GE_CORE_ERROR("Unsupported Uniform type selected.");
		}
		
		}



		GE_CORE_ERROR("Invalid Rendering API selected");
		return nullptr;
	}


}


