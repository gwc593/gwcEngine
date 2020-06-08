#pragma once
#include<string>
#include<glm/glm.hpp>
namespace gwcEngine
{
	class Shader
	{
	public:
		Shader(const std::string& vertextSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_Renderer_ID;
	};
}