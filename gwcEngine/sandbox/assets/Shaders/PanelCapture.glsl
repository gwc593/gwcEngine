#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform float u_border_width;
		
out vec2 v_TexCoord;
out float border_width;
			
void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	border_width = u_border_width;
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;
			
in vec2 v_TexCoord;
in float border_width;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
	
   float maxX = 1.0 - border_width;
   float minX = border_width;
   float maxY = maxX / 1.0;
   float minY = minX / 1.0;
	
	if (v_TexCoord.x < maxX && v_TexCoord.x > minX &&
       v_TexCoord.y < maxY && v_TexCoord.y > minY) {
     color = texture(u_Texture, v_TexCoord);
   } else {
     color = vec4(1.0,1.0,1.0,1.0);
   }
}