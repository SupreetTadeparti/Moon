#include "Scene.hpp"

namespace Moon
{
	Scene::Scene() : m_Camera(nullptr)
	{
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_Models.push_back(entity->GetModel());
		m_Entities[entity->GetModel()].push_back(entity);
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		List<Entity*> entities = m_Entities[entity->GetModel()];
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		m_Entities[entity->GetModel()] = entities;
	}

	void Scene::AddText(Text* text)
	{
		for (Entity* entity : text->GetCharacters())
		{
			AddEntity(entity);
		}
	}
}