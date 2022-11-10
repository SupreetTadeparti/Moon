#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in mat4 a_Model;

out vec2 v_TextureCoord;
out vec3 v_Normal;

uniform bool u_Fixed;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	vec4 worldPosition = a_Model * a_Position;
	vec4 viewWorldPosition = u_Fixed ? worldPosition : u_View * worldPosition;
	gl_Position = u_Projection * viewWorldPosition;
	v_TextureCoord = a_TextureCoord;
	v_Normal = mat3(transpose(inverse(a_Model))) * a_Normal;
}