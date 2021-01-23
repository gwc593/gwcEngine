#pragma once
#include<string>
#include<glm/glm.hpp>
#include"gwcEngine/Renderer/Shader/Buffer.h"
#include"ShaderUniform.h"
#include"gwcEngine/Renderer/Texture.h"
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

		virtual void UploadUniformBool(const std::string& name, bool state) = 0;

		virtual void UploadUniformInt(const std::string& name, const int& Int) = 0;

		virtual void UploadUniformFloat(const std::string& name, const float& Float) = 0;

		virtual void UploadUniformVec2(const std::string& name, const glm::vec2& vec3) = 0;
		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vec3) = 0;
		virtual void UploadUniformVec4(const std::string& name, const glm::vec4& vec4) = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;

		virtual void UploadTexture2D(const std::string& name, const Ref<Texture2D>& texture) = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& shaderPath);

		static const std::vector<std::weak_ptr<Shader>>& GetShaders() { return m_Shaders; }


		const std::vector<ShaderUniform*> GetUniforms()const { return m_Uniforms; }
	protected:
		std::vector<ShaderUniform*> m_Uniforms;
		static std::vector<std::weak_ptr<Shader>> m_Shaders;

	};
}