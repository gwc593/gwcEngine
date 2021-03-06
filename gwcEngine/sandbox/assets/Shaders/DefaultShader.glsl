#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
		
out vec3 v_Position;
out vec4 v_normColour;
			
void main()
{
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	v_Position = a_Position;
	

	v_normColour = vec4((mat3(transpose(inverse(u_Transform))) * a_Normal),1.0);
	

}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

in vec4 v_normColour;


void main()
{
	color = v_normColour;
}
