#pragma once
#include "gwcEngine/Renderer/Shader/Shader.h"

namespace gwcEngine 
{

	class Material
	{
	public:
		Material():
		m_IsModified(false)
		{
			if (s_DefaultShader == nullptr)
				s_DefaultShader = Shader::Create("assets/Shaders/DefaultLitShader2.glsl");
			m_Shader = s_DefaultShader;
			m_Uniforms = s_DefaultShader->m_Uniforms;
		};

		Material(Ref<Shader> shader) :
			m_Shader(shader),m_IsModified(false){m_Uniforms = shader->m_Uniforms;};

		void SetShader(const Ref<Shader>& shader);

		template<typename T>
		void SetValue(const std::string& name, T value)
		{
			std::vector<ShaderUniform*>::iterator it = m_Uniforms.begin();

			for (; it != m_Uniforms.end(); it++) {
				if ((*it)->GetName() == name)
					break;
			}
			if(it != m_Uniforms.end())
				(*it)->SetValue(value);
		};

		const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }

	private:
		Ref<Shader> m_Shader;
		std::vector<ShaderUniform*> m_Uniforms;
		bool m_IsModified;
		static Ref<Shader> s_DefaultShader;
	};


}
