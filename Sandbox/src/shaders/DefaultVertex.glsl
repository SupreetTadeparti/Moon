#version 450 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in mat4 a_Model;
//layout (location = 4) in float a_FragmentType;
//layout (location = 6) in sampler2D a_Texture;

/*
	a_FragmentType :-
	0 - Color
	1 - Texture
*/

out vec2 v_TextureCoord;
out vec3 v_Normal;
out float v_FragmentType;
//out vec4 v_Color;
//out sampler2D v_Texture;

uniform bool u_Fixed;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	vec4 worldPosition = a_Model * a_Position;
	vec4 viewWorldPosition = u_Fixed ? worldPosition : u_View * worldPosition;
	gl_Position = u_Projection * viewWorldPosition;
	v_TextureCoord = a_TextureCoord;
//	v_FragmentType = a_FragmentType;
//	v_Texture = a_Texture;
	v_Normal = mat3(transpose(inverse(a_Model))) * a_Normal;
}