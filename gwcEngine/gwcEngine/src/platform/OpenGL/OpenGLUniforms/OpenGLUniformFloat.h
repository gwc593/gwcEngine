#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformFloat : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformFloat() = default;

		OpenGLUniformFloat(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(float(0.5f))
		{
			m_name = name;
		}

		float GetValue() { return m_value; }
		virtual void SetValue(const float& value) override { m_value = value; m_shader->UploadUniformFloat(m_name, m_value); }

	private:
		float m_value;
		Shader* m_shader;
	};
}
