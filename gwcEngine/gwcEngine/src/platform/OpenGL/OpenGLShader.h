#pragma once
#include "gwcEngine/Renderer/Shader/Shader.h"
namespace gwcEngine 
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertextSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void ParseAttributs() override {};
		virtual void ParseUniforms() override;

		virtual void UploadUniformInt(const std::string& name, const int& Int) override;
		
		virtual void UploadUniformFloat(const std::string& name, const float& Float) override;
		
		virtual void UploadUniformVec2(const std::string& name, const glm::vec3& vec3) override;
		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vec3) override;
		virtual void UploadUniformVec4(const std::string& name, const glm::vec4& vec4) override;
		
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
	private:
		uint32_t m_Renderer_ID;
	};
}


