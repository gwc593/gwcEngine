#include "gepch.h"
#include "Material.h"
#include<glad/glad.h>
namespace gwcEngine
{
	
	void Material::SetShader(std::shared_ptr<Shader> shader)
	{
		m_Uniforms = shader->m_Uniforms;
	}

}


