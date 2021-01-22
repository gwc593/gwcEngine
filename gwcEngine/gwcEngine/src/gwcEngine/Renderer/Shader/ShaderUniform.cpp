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
			case ShaderDataType::Float:return new OpenGLUniformFloat(name, shader);
			case ShaderDataType::Vec2:return new OpenGLUniformVec2(name, shader);
			case ShaderDataType::Vec3:return new OpenGLUniformVec3(name, shader);
			case ShaderDataType::Vec4:return new OpenGLUniformVec4(name, shader);
			case ShaderDataType::Mat3:break;
			case ShaderDataType::Mat4: return new OpenGLUniformMat4(name, shader);
			case ShaderDataType::Int:break;
			case ShaderDataType::Int2:break;
			case ShaderDataType::Int3:break;
			case ShaderDataType::Int4:break;
			case ShaderDataType::Bool:break;
			case ShaderDataType::Sampler2D: return new OpenGLUniformTexture2D(name, shader);
			default: break;
			}
			GE_CORE_WARN("{0} (type) {1} is not currently supported by the material system and therefore cannot be modified at runtime", name, type);
			return nullptr;
		}
		
		}



		GE_CORE_ERROR("Invalid Rendering API selected");
		return nullptr;
	}


}


