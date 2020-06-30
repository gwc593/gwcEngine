#pragma once
#include<string>
#include<glm/glm.hpp>
#include"gwcEngine/Renderer/Shader/Buffer.h"
#include"ShaderUniform.h"
namespace gwcEngine
{
	class ShaderUniform;

	class Shader
	{
	public:
		
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void ParseUniforms() = 0;
		virtual void ParseAttributs() = 0;

		virtual void UploadUniformInt(const std::string& name, const int& Int) = 0;

		virtual void UploadUniformFloat(const std::string& name, const float& Float) = 0;

		virtual void UploadUniformVec2(const std::string& name, const glm::vec3& vec3) = 0;
		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vec3) = 0;
		virtual void UploadUniformVec4(const std::string& name, const glm::vec4& vec4) = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);


		std::vector<ShaderUniform*> m_Uniforms;
	private:
	};
}