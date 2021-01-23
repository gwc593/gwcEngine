#include "gepch.h"
#include "Material.h"
#include<glad/glad.h>
namespace gwcEngine
{
	
	Ref<Shader> Material::s_DefaultShader = nullptr;

	void Material::SetShader(const Ref<Shader>& shader)
	{
		m_Shader = shader;
		m_Uniforms = shader->GetUniforms();
	}

}


