#include "CameraController.hpp"

namespace Moon
{
	FirstPersonCamera::FirstPersonCamera(Camera* camera, Double speed, Bool locked, Bool click) : m_Click(click), m_Speed(speed)
	{
		SetCamera(camera);
		Window::SetCursorType(CursorType::Hidden);
		OnMouseMove([camera](Vec2 pos) 
			{
				Double centerX = Window::GetWidth() / 2.0;
				Double centerY = Window::GetHeight() / 2.0;
				Double dx = pos.x - centerX;
				Double dy = pos.y - centerY;
				camera->Rotate(Vec3(dy / 100.0, dx / 100.0, 0));
				Window::SetCursorPos(Vec2(centerX, centerY));
			});
		OnUpdate([this]() 
			{
				Vec3 rotation = this->GetCamera()->GetRotation();
				if (EventHandler::KeyDown("w") || EventHandler::KeyDown("UP"))
					this->GetCamera()->Move(Vec3(this->GetSpeed() * sin(rotation.y), 0, this->GetSpeed() * -cos(rotation.y)));
				if (EventHandler::KeyDown("a") || EventHandler::KeyDown("LEFT"))
					this->GetCamera()->Move(Vec3(this->GetSpeed() * -cos(rotation.y), 0, this->GetSpeed() * -sin(rotation.y)));
				if (EventHandler::KeyDown("s") || EventHandler::KeyDown("DOWN"))
					this->GetCamera()->Move(Vec3(this->GetSpeed() * -sin(rotation.y), 0, this->GetSpeed() * cos(rotation.y)));
				if (EventHandler::KeyDown("d") || EventHandler::KeyDown("RIGHT"))
					this->GetCamera()->Move(Vec3(this->GetSpeed() * cos(rotation.y), 0, this->GetSpeed() * sin(rotation.y)));
				if (EventHandler::KeyDown(" "))
					this->GetCamera()->Move(Vec3(0, this->GetSpeed(), 0));
				if (EventHandler::KeyDown("LSHIFT"))
					this->GetCamera()->Move(Vec3(0, -this->GetSpeed(), 0));
			});
	}
}