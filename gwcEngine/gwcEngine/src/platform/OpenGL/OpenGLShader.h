#pragma once
#include "gwcEngine/Renderer/Shader/Shader.h"
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace gwcEngine 
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertextSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& shaderPath);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void ParseAttributs() override {};
		virtual void ParseUniforms() override;

		virtual void UploadUniformInt(const std::string& name, const int& Int) override;
		
		virtual void UploadUniformFloat(const std::string& name, const float& Float) override;
		
		virtual void UploadUniformVec2(const std::string& name, const glm::vec2& vec3) override;
		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vec3) override;
		virtual void UploadUniformVec4(const std::string& name, const glm::vec4& vec4) override;
		
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
	
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& shaderSource);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderElements);
	private:
		uint32_t m_Renderer_ID;
	};
}


