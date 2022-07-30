#pragma once

#include "Core.h"
#include "Text.hpp"
#include "Camera.hpp"
#include "EventController.hpp"

namespace Moon
{
	class Scene : public CallbackEventController
	{
	public:
		MOON_API Scene();
		MOON_API void AddEntity(Entity* entity);
		MOON_API void AddText(Text* entity);
		MOON_API void RemoveEntity(Entity* entity);
		MOON_API inline void SetCamera(Camera* camera) { m_Camera = camera; }
		MOON_API inline Camera* GetCamera() const { return m_Camera; }
		MOON_API inline HashMap<Model*, List<Entity*>> GetEntities() const { return m_Entities; }
		MOON_API inline List<Model*> GetModels() const { return m_Models; }
	private:
		Camera* m_Camera;
		List<Model*> m_Models;
		HashMap<Model*, List<Entity*>> m_Entities;
	};
}