#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
layout (location = 2) in vec3 a_Normal;

out vec2 v_TextureCoord;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform bool u_Fixed;

void main()
{
	vec4 worldPosition = u_Model * a_Position;
	vec4 viewWorldPosition = u_Fixed ? worldPosition : u_View * worldPosition;
	gl_Position = u_Projection * viewWorldPosition;
	v_TextureCoord = a_TextureCoord;
	v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
}