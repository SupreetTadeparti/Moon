#include "Scene.hpp"

namespace Moon
{
	Scene::Scene() : m_Camera(nullptr), m_AmbientLight(nullptr), m_DirectionalLight(nullptr), m_SpotLight(nullptr)
	{
	}

	void Scene::CreateTransformationBuffers(Model* model, List<Mat4>* transformations)
	{
		if (m_Buffers.find(model) != m_Buffers.end())
		{
			m_Buffers[model]->SetData(transformations->data(), transformations->size());
		}
		else
		{
			m_Buffers[model] = new Buffer(transformations->data(), transformations->size());
			for (int i = 0; i < 4; i++)
			{
				VertexBuffer* vbo = new VertexBuffer(3 + i, 4, sizeof(Mat4), i * sizeof(Vec4), m_Buffers[model], AttributeAdvanceRate::Shape);
				model->GetVertexArray()->AddVBO(vbo);
			}
		}
	}

	void Scene::UpdateTransformationBuffers(Model* model, List<Entity*>* entities)
	{
		for (Uint i = 0; i < m_Entities[model].first.size(); i++)
		{
			Entity* entity = m_Entities[model].first[i];
			if (entity->GetModified())
			{
				Mat4 transformation = entity->GetModelMatrix();
				m_Buffers[model]->UpdateData(&transformation, i);
				entity->SetModified(false);
			}
		}
	}

	void Scene::UpdateModels()
	{
		// Add / Remove Entity Updating
		for (Model* model : m_ModifiedModels)
		{
			CreateTransformationBuffers(model, &(m_Entities[model].second));
		}
		m_ModifiedModels.clear();

		// Update Entity Updating
		for (Model* model : m_Models)
		{
			if (model->GetModified())
			{
				UpdateTransformationBuffers(model, &m_Entities[model].first);
				model->SetModified(false);
			}
		}
	}

	void Scene::AddEntity(Entity* entity)
	{
		Model* model = entity->GetModel();
		
		m_ModifiedModels.insert(model);
		m_Models.insert(model);

		if (model->GetTransparency()) m_TranslucentModels.insert(model);
		
		List<Entity*>* entities = &m_Entities[model].first;
		List<Mat4>* transformations = &m_Entities[model].second;
		
		entities->push_back(entity);
		transformations->push_back(entity->GetModelMatrix());
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		Model* model = entity->GetModel();

		m_ModifiedModels.insert(model);

		List<Entity*>* entities = &m_Entities[model].first;
		List<Mat4>* transformations = &m_Entities[model].second;

		List<Entity*>::iterator idx = std::find(entities->begin(), entities->end(), entity);
		transformations->erase(transformations->begin() + (idx - entities->begin()));
		entities->erase(std::find(entities->begin(), entities->end(), entity));

		delete entity;
	}

	void Scene::SetCameraController(CameraController* cc)
	{
		if (m_Camera == nullptr) m_Camera = cc->GetCamera();

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