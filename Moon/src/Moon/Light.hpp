#pragma once

#include "Core.h"

namespace Moon
{
	class Light
	{
	public:
		MOON_API inline Vec3 GetColor() const { return m_Color; }
	protected:
		Vec3 m_Color;
	};

	class AmbientLight : public Light
	{
	public:
		MOON_API AmbientLight(Float brightness, Vec3 color=Vec3(255, 255, 255));
		MOON_API inline Float GetBrightness() const { return m_Brightness; }
	private:
		Float m_Brightness;
	};

	class DirectionalLight : public Light
	{
	public:
		MOON_API DirectionalLight(Vec3 angle, Vec3 color=Vec3(255, 255, 255));
		MOON_API inline Vec3 GetDirection() const { return m_Angle; }
	private:
		Vec3 m_Angle;
	};

	class SpotLight : public Light
	{
	public:
		MOON_API SpotLight(Vec3 position, Vec3 color = Vec3(255, 255, 255));
	private:
		Vec3 m_Position;
	};
}
