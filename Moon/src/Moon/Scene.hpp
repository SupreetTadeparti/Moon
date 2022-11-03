#pragma once

#include "Core.h"
#include "Text.hpp"
#include "CameraController.hpp"
#include "EventController.hpp"
#include "Light.hpp"

namespace Moon
{
	class Scene : public CallbackEventController
	{
	public:
		MOON_API Scene();
		MOON_API void AddEntity(Entity* entity);
		MOON_API void AddText(Text* entity);
		MOON_API void RemoveEntity(Entity* entity);
		MOON_API inline void SetCameraController(CameraController* cc);
		MOON_API inline void SetAmbientLight(AmbientLight* light) { m_AmbientLight = light; };
		MOON_API inline AmbientLight* GetAmbientLight() { return m_AmbientLight; };
		MOON_API inline void SetDirectionalLight(DirectionalLight* light) { m_DirectionalLight = light; };
		MOON_API inline DirectionalLight* GetDirectionalLight() { return m_DirectionalLight; };
		MOON_API inline void SetSpotLight(SpotLight* light) { m_SpotLight = light; };
		MOON_API inline SpotLight* GetSpotLight() { return m_SpotLight; };
		MOON_API inline void SetCamera(Camera* camera) { m_Camera = camera; }
		MOON_API inline Camera* GetCamera() const { return m_Camera; }
		MOON_API inline HashMap<Model*, List<Entity*>> GetEntities() const { return m_Entities; }
		MOON_API inline HashMap<Model*, List<Entity*>> GetAlphaEntities() const { return m_AlphaEntities; }
		MOON_API inline Set<Model*> GetModels() const { return m_Models; }
	private:
		Camera* m_Camera;
		AmbientLight* m_AmbientLight;
		DirectionalLight* m_DirectionalLight;
		SpotLight* m_SpotLight;
		Set<Model*> m_Models;
		HashMap<Model*, List<Entity*>> m_Entities;
		HashMap<Model*, List<Entity*>> m_AlphaEntities;
	};
}