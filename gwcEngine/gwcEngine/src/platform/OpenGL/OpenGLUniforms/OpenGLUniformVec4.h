#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine 
{
	class OpenGLUniformVec4 : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformVec4() = default;

		OpenGLUniformVec4(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(glm::vec4(0.5f))
		{
			m_name = name;
		}

		glm::vec4 GetValue() { return m_value; }
		virtual void SetValue(const glm::vec4& value) override { m_value = value; m_shader->UploadUniformVec4(m_name, m_value); }

	private:
		glm::vec4 m_value;
		Shader* m_shader;
	};
}
