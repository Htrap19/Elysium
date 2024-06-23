// #type vertex
#version 410

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in int  a_TexIndex;
layout (location = 3) in int  a_ModelIndex;
layout (location = 4) in vec4 a_Color;

out vec3 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * vec4(a_Pos, 1.0);

	v_TexCoord = a_Pos;
}

// #type fragment
#version 410

layout (location = 0) out vec4 o_Color;

in vec3 v_TexCoord;

uniform samplerCube u_SkyBoxSampler;

void main()
{
	o_Color = texture(u_SkyBoxSampler, v_TexCoord);
}