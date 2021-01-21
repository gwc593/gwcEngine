#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformVec2 : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformVec2() = default;

		OpenGLUniformVec2(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(glm::vec2(0.5f))
		{
			m_name = name;
		}

		glm::vec2 GetValue() { return m_value; }
		virtual void SetValue(const glm::vec2& value) override { m_value = value; m_shader->UploadUniformVec2(m_name, m_value); }

	private:
		glm::vec2 m_value;
		Shader* m_shader;
	};
}
