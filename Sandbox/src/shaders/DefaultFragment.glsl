#version 330 core

in vec2 v_TextureCoord;
in vec3 v_Normal;

out vec4 o_Color;

/*
	1 - Color
	2 - Texture
*/
uniform int u_FragmentType;

uniform float u_AmbientLightBrightness;
uniform bool u_AmbientLightActivated;
uniform vec3 u_AmbientLightColor;

uniform bool u_DirectionalLightActivated;
uniform vec3 u_DirectionalLightColor;
uniform vec3 u_DirectionalLightDirection;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 fragColor = u_FragmentType == 1 ? u_Color : texture(u_Texture, v_TextureCoord);
	if (fragColor.a < 0.1) discard;
	vec3 color = vec3(0.0f);
	if (u_AmbientLightActivated)
	{
		vec3 ambient = u_AmbientLightBrightness * u_AmbientLightColor;
		color += ambient;
	}
	if (u_DirectionalLightActivated)
	{
		vec3 normal = normalize(v_Normal);
		vec3 lightDirection = normalize(-u_DirectionalLightDirection);
		vec3 diffuse = max(dot(normal, lightDirection), 0.0) * u_DirectionalLightColor;
		color += diffuse;
	}
	color = max(color, 1.0f);
	o_Color = vec4(color * fragColor.rgb, fragColor.a);
}