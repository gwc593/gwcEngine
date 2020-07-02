#include "gepch.h"
#include "Material.h"
#include<glad/glad.h>
namespace gwcEngine
{
	
	void Material::SetShader(const Ref<Shader>& shader)
	{
		m_Shader = shader;
		m_Uniforms = shader->m_Uniforms;
	}

}


