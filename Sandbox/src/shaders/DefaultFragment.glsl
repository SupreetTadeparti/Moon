#version 450 core

in vec2 v_TextureCoord;
in vec3 v_Normal;
//in vec4 v_Color;
//in float v_FragmentType;
//in sampler2D v_Texture;

out vec4 o_Color;

uniform float u_AmbientLightBrightness;
uniform bool u_AmbientLightActivated;
uniform vec3 u_AmbientLightColor;

uniform bool u_DirectionalLightActivated;
uniform vec3 u_DirectionalLightColor;
uniform vec3 u_DirectionalLightDirection;

uniform bool u_Text;

void main()
{
//	vec4 fragColor = v_FragmentType ? v_Color : texture(v_Texture, v_TextureCoord);
	//vec4 fragColor = v_Color;

//	if (fragColor.a < 0.1) discard;
//
//	if (u_Text) {
//		o_Color = vec4(1.0, 1.0, 1.0, fragColor.r);
//		return;
//	}
/*
	float baseBrightness = (!u_AmbientLightActivated && !u_DirectionalLightActivated ? 1.0f : 0.0f);
	vec3 color = vec3(baseBrightness);

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
*/
	//o_Color = vec4(color * fragColor.rgb, fragColor.a);
	//o_Color = vec4(clamp(v_Color, 0.0, 1.0).xyz, 1.0);
	//o_Color = v_Color;
	//o_Color = vec4(fragColor.xyz, 1);
	o_Color = vec4(1.0, 0.0, 0.0, 1.0);
}