#pragma once

#include "Core.h"
#include "Camera.hpp"
#include "EventController.hpp"

namespace Moon
{
	class CameraController : public CallbackEventController
	{
	public:
		MOON_API inline Camera* GetCamera() { return m_Camera; }
		MOON_API inline void SetCamera(Camera* camera) { m_Camera = camera; }
	protected:
		Camera* m_Camera;
	};

	class FirstPersonCamera : public CameraController
	{
	public:
		MOON_API FirstPersonCamera(Camera* camera, Double speed=0.02, Bool locked=false, Bool click=false);
		MOON_API inline void SetSpeed(Double speed) { m_Speed = speed; }
		MOON_API inline Double GetSpeed() { return m_Speed; }
	private:
		Double m_Speed;
		Bool m_Click;
	};

	class ThirdPersonCamera : public CameraController
	{
	};

	class TwoDCamera : public CameraController
	{
	};
}

