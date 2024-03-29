#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform float u_border_width;

out vec3 v_Position;
out vec2 v_TexCoord;
out float border_width;
			
void main()
{
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	v_Position = a_Position;
	v_TexCoord = a_TexCoord;
	border_width = u_border_width;
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec2 v_TexCoord;
in float border_width;

void main()
{
   float maxX = 1.0 - border_width;
   float minX = border_width;
   float maxY = maxX / 1.0;
   float minY = minX / 1.0;
	
	
	color = vec4(0.0,0.0,0.0,1.0);
	
	if (v_TexCoord.x < maxX && v_TexCoord.x > minX &&
       v_TexCoord.y < maxY && v_TexCoord.y > minY) {
     color = vec4(0.0,0.0,0.0,1.0);
   } else {
     color = vec4(1.0,1.0,1.0,1.0);
   }
}
