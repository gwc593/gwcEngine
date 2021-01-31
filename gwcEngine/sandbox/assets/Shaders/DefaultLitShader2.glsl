#type vertex
#version 440
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Colour = vec4(0.94,0.93,0.9,1.0);

out vec4 v_Position;
out vec2 v_UV;
out vec3 v_Normal;
out vec4 v_Colour;

void main()
{
	gl_Position = u_ViewProjection * u_Transform* vec4(a_Position,1.0);
	v_Position =  u_Transform* vec4(a_Position,1.0);
	
	v_UV = a_TexCoord;
	
	v_Normal = (mat3(transpose(inverse(u_Transform))) * a_Normal);
	
	v_Colour = u_Colour;
}

#type fragment
#version 440

layout(location = 0) out vec4 fragColour;

const int MaxLights = 20;

struct LightProps{
	bool isEnabled;
	bool isLocal; //true for point and spot
	bool isSpot;
	vec4 ambient;
	vec4 colour;
	vec4 position;
	vec4 halfVector;
	vec4 coneDirection;
	float spotCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float strength;
};

in vec3 v_Normal;
in vec4 v_Colour;
in vec4 v_Position;


uniform vec4 u_Ambient = vec4(0.1,0.1,0.1,1);
uniform float u_Shininess = 100;
uniform vec3 u_EyeDirection = vec3(0,0,-1);

layout(std140) uniform LightBlock
{
	int b_NumLights;
	LightProps b_Lights[MaxLights];
};

void main()
{
	vec3 scatteredLight = vec3(u_Ambient.rgb);
	vec3 reflectedLight = vec3(0.0);
	
	
//loop over all lights
for(int light = 0; light<b_NumLights; ++light){
	if(!b_Lights[light].isEnabled)
		continue;
		
	vec3 halfVector = vec3(0.0);
	
	vec3 lightDirection = b_Lights[light].position.xyz;
	float attenuation = 1.0;
	
	//for local lights, compute per fragment direction halfVector and attenuation
	if(b_Lights[light].isLocal){
		lightDirection = lightDirection - vec3(v_Position);
		float lightDistance = length(lightDirection);
		lightDirection = lightDirection/lightDistance;
		
		attenuation = 1.0/
			(b_Lights[light].constantAttenuation
			+ b_Lights[light].linearAttenuation * lightDistance
			+ b_Lights[light].quadraticAttenuation * lightDistance * lightDistance);
			
		if(b_Lights[light].isSpot){
			float spotCos = dot(lightDirection,-b_Lights[light].coneDirection.xyz);
			if(spotCos < b_Lights[light].spotCutoff)
				attenuation = 0.0;
			else
				attenuation *= pow(spotCos,b_Lights[light].spotExponent);
		}
		
		halfVector = normalize(lightDirection + u_EyeDirection);
		
	} else {
		halfVector = b_Lights[light].halfVector.xyz;
	}
	
	float diffuse = max(0.0,dot(v_Normal, lightDirection));
	float specular = max(0.0,dot(v_Normal,halfVector));
	
	if(diffuse == 0.0)
		specular = 0.0;
	else
		specular = pow(specular,u_Shininess)* b_Lights[light].strength;
		
	scatteredLight += b_Lights[light].ambient.rgb*attenuation*b_Lights[light].strength
					+ b_Lights[light].colour.rgb * diffuse * attenuation*b_Lights[light].strength;
					
	reflectedLight += b_Lights[light].colour.rgb * specular * attenuation*b_Lights[light].strength;

}

vec3 rgb = min(v_Colour.rgb*scatteredLight + reflectedLight,vec3(1.0));
fragColour = vec4(rgb,v_Colour.a);
	
}
