#pragma once

#include "Core.h"

namespace Moon
{
	class RigidBody
	{
	public:
		MOON_API inline void EnableGravity() { m_GravityEnabled = true; };
		MOON_API inline void DisableGravity() { m_GravityEnabled = false; };
		MOON_API inline void SetVelocity(Vec3 velocity) { m_Velocity = velocity; };
		MOON_API inline Vec3 GetVelocity() const { return m_Velocity; }
	private:
		Bool m_GravityEnabled = false;
		Vec3 m_Velocity;
	};
}

