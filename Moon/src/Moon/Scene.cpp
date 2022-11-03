#include "Scene.hpp"

namespace Moon
{
	Scene::Scene() : m_Camera(nullptr), m_AmbientLight(nullptr), m_DirectionalLight(nullptr), m_SpotLight(nullptr)
	{
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_Models.insert(entity->GetModel());
		(entity->GetTransparency() ? m_AlphaEntities : m_Entities)[entity->GetModel()].push_back(entity);
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		HashMap<Model*, List<Entity*>>* models = &(entity->GetTransparency() ? m_AlphaEntities : m_Entities);
		(*models)[entity->GetModel()].erase(std::remove((*models)[entity->GetModel()].begin(), (*models)[entity->GetModel()].end(), entity), (*models)[entity->GetModel()].end());
		delete entity;
	}

	void Scene::SetCameraController(CameraController* cc)
	{
		AddChildCallback(cc, EventType::MouseMove, [](Vec2) -> bool { return true; });
		AddChildCallback(cc, EventType::Update, []() -> bool { return true; });
	}

	void Scene::AddText(Text* text)
	{
		for (Entity* entity : text->GetCharacters())
		{
			AddEntity(entity);
		}
	}
}