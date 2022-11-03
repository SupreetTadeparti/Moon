#include "Light.hpp"

namespace Moon
{
	AmbientLight::AmbientLight(Float brightness, Vec3 color) : m_Brightness(brightness)
	{
		m_Color = color;
	}

	DirectionalLight::DirectionalLight(Vec3 angle, Vec3 color) : m_Angle(angle)
	{
		m_Color = color;
	}

	SpotLight::SpotLight(Vec3 position, Vec3 color) : m_Position(position)
	{
		m_Color = color;
	}
}