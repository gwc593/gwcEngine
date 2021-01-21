#pragma once
#pragma once
#include"gwcEngine/Renderer/Shader/Shader.h"
#include"gwcEngine/Renderer/Texture.h"
#include <glm/glm.hpp>
namespace gwcEngine
{
	class OpenGLUniformTexture2D : public ShaderUniform
	{
	public:

		virtual ~OpenGLUniformTexture2D() = default;

		OpenGLUniformTexture2D(std::string name, Shader* shader)
			:
			m_shader(shader),
			m_value(nullptr)
		{
			m_name = name;
		}

		Ref<Texture2D> GetValue() { return m_value; }
		virtual void SetValue(const Ref<Texture2D>& value) override { m_value = value; m_shader->UploadTexture2D(m_name, m_value); }

	private:
		Ref<Texture2D> m_value;
		Shader* m_shader;
	};
}
