#shader vertex
#version 430 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texpos;

out vec2 v_TexPos;

uniform mat4 u_MVP;

void main()
{
	mat4 a = mat4(1.0);
	gl_Position = u_MVP * pos;
	v_TexPos = texpos;
}

#shader fragment
#version 430 core

out vec4 FragColor;

in vec2 v_TexPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main()
{
	float k = 2.0;
	vec2 v_TexPos1 = k * v_TexPos + vec2(- k / 2 + 0.5, -k / 2 + 0.5);
	vec4 texColor = texture(u_Texture, v_TexPos);
	vec4 texColor1 = texture(u_Texture1, v_TexPos1);
	if(texColor1.r + texColor1.g + texColor.b < 0.01) texColor1.a = 0.0;
	if(texColor1.a != 0.0) FragColor = mix(texColor1, u_Color, 0.0);
	else FragColor = mix(texColor, u_Color, 0.0);
}