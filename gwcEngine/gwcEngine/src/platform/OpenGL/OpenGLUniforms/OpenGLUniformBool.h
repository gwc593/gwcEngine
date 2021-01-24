#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformBool : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformBool() = default;

		OpenGLUniformBool(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(false)
		{
			m_name = name;
		}

		float GetValue() { return m_value; }
		virtual void SetValue(const bool& value) override { m_value = value; m_shader->UploadUniformBool(m_name, m_value); }

	private:
		bool m_value;
		Shader* m_shader;
	};
}
