#pragma once

#include "Core.h"

namespace Moon
{
	class Camera
	{
	public:
		MOON_API Camera();
		MOON_API void Move(Vec3 translation);
		MOON_API void Move(Double x, Double y, Double z);
		MOON_API void Rotate(Vec3 rotation);
		MOON_API void Rotate(Double x, Double y, Double z);
		MOON_API void SetPosition(Vec3 position);
		MOON_API void SetRotation(Vec3 rotation);
		MOON_API inline Vec3 GetPosition() const { return m_Position; }
		MOON_API inline Vec3 GetRotation() const { return m_Rotation; }
		MOON_API inline Mat4 GetViewMatrix() const { return m_ViewMatrix; }
	private:
		void UpdateViewMatrix();
		Vec3 m_Position;
		Vec3 m_Rotation;
		Mat4 m_TranslationMatrix;
		Mat4 m_RotationMatrix;
		Mat4 m_ViewMatrix;
	};
}