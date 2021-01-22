#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Colour = vec4(0.94,0.93,0.9,1.0);
		
out vec4 v_Position;
out vec2 v_UV;
out vec4 v_Normal;
out vec4 v_Colour;


void main()
{
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	v_Position =  u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	
	v_UV = a_TexCoord;
	
	v_Normal = vec4((mat3(transpose(inverse(u_Transform))) * a_Normal),1.0);
	
	v_Colour = u_Colour;

}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

const int MaxLights = 20;

struct LightProps{
	bool isEnabled;
	bool isLocal; //true for point and spot
	bool isSpot;
	vec3 ambient;
	vec3 colour;
	vec3 position;
	vec3 halfVector;
	vec3 coneDirection;
	float spotCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

in vec4 v_Normal;
in vec4 v_Colour;

uniform vec4 u_Ambient = vec4(0.1,0.1,0.1,1);
uniform LightProps Lights[MaxLights];

void main()
{
	for(int i = 0; i<MaxLights; i++){
		if(Lights[i].isEnabled){
			int a = 1;
		}
	}
	color = min(v_Colour*u_Ambient,vec4(1.0))+vec4(v_Normal.x)*u_Ambient;
}
