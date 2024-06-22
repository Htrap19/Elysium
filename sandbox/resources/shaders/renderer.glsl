// #type vertex
#version 410

#define MAX_MODELMATRICES_COUNT 32 // As per the renderer specification

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in int  a_TexIndex;
layout (location = 3) in int  a_ModelIndex;
layout (location = 4) in vec4 a_Color;

out vec2 v_TexCoord;
flat out int v_TexIndex;
out vec4 v_Color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model[MAX_MODELMATRICES_COUNT];

void main()
{
	gl_Position = u_Projection * u_View * u_Model[a_ModelIndex] * vec4(a_Pos, 1.0);

	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_Color = a_Color;
}

// #type fragment
#version 410

#define MAX_TEXTURE_COUNT 32 // As per the renderer specification

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
flat in int v_TexIndex;
in vec4 v_Color;

uniform sampler2D u_Texture[MAX_TEXTURE_COUNT];

void main()
{
	o_Color = texture(u_Texture[v_TexIndex], v_TexCoord) * v_Color;
}