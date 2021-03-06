#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
		
out vec3 v_Position;
			
void main()
{
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	v_Position = a_Position;
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;
layout(location = 1) out float pickID;
uniform vec4 u_Colour;

in vec3 v_Position;

void main()
{
	color = u_Colour;
}
