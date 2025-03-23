#pragma once

#include "Core.h"

namespace Moon
{
	class Math
	{
	public:
		static const LongDouble PI;
		MOON_API static Double Radians(Double degrees);
		MOON_API static Double Degrees(Double radians);
		template <typename T>
		MOON_API static Mat4 Perspective(T fov, T aspect, T zNear, T zFar);
		template <typename... Args>
		MOON_API static Mat4 Ortho(Args... args);
	};
}