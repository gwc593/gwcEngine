#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformMat4 : public ShaderUniform
	{
	public:
		virtual ~OpenGLUniformMat4() = default;

		OpenGLUniformMat4(std::string name, Shader* shader)
			:
			 m_shader(shader), 
			m_value(glm::mat4(1.0f))
		{
			m_name = name;
		}

		glm::mat4 GetValue() { return m_value; }
		void SetValue(const glm::mat4& value) override { m_value = value; m_shader->UploadUniformMat4(m_name, m_value); }

	private:
		glm::mat4 m_value;
		Shader* m_shader;
	};



}