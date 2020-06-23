#pragma once
#include "gwcEngine/Renderer/Shader/Shader.h"

namespace gwcEngine 
{

	class Material
	{
	public:
		Material():
		m_Shader(nullptr){};

		Material(std::shared_ptr<Shader> shader) :
			m_Shader(shader){m_Uniforms = shader->m_Uniforms;};

		void SetShader(std::shared_ptr<Shader> shader);

		template<typename T>
		void SetValue(const std::string& name, T value)
		{
			std::vector<ShaderUniform*>::iterator it = m_Uniforms.begin();

			for (; it != m_Uniforms.end(); it++) {
				if ((*it)->GetName() == name)
					break;
			}
			(*it)->SetValue(value);
		};

		const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }

	private:
		std::shared_ptr<Shader> m_Shader;
		std::vector<ShaderUniform*> m_Uniforms;
	};


}
