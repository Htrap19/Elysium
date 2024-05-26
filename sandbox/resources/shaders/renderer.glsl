// #type vertex
#version 410

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Pos, 1.0);
	v_TexCoord = a_TexCoord;
}

// #type fragment
#version 410

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, v_TexCoord) * u_Color;
}