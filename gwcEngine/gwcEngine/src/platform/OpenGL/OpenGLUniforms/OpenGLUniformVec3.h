#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformVec3 : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformVec3() = default;

		OpenGLUniformVec3(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(glm::vec3(0.5f))
		{
			m_name = name;
		}

		glm::vec3 GetValue() { return m_value; }
		virtual void SetValue(const glm::vec3& value) override { m_value = value; m_shader->UploadUniformVec3(m_name, m_value); }

	private:
		glm::vec3 m_value;
		Shader* m_shader;
	};
}
