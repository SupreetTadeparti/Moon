#include "Renderer.hpp"

namespace Moon
{
	std::unordered_map<Model*, std::vector<Entity*>> Renderer::s_ModelEntityMap;
	Vec3 Renderer::s_BackgroundColor(0.7f);

	void Renderer::AddEntity(Entity* entity)
	{
		s_ModelEntityMap[entity->GetModel()].push_back(entity);
	}

	void Renderer::AddText(Text* text)
	{
		for (Entity* entity : text->GetCharacters())
		{
			AddEntity(entity);
		}
	}

	void Renderer::Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b, 1.0f);
	}

	void Renderer::Render()
	{
		for (auto& pair : s_ModelEntityMap)
		{
			Model* model = pair.first;
			model->GetVertexArray()->Bind();
			model->GetVertexArray()->GetIndexBuffer()->Bind();
			model->GetShader()->Bind();
			for (auto& entity : pair.second)
			{
				MaterialType materialType = entity->GetMaterial()->GetMaterialType();
				if (materialType == MaterialType::Color)
				{
					model->GetShader()->SetUniformVec4("u_Color", entity->GetMaterial()->GetColor()->GetColor());
				}
				else if (materialType == MaterialType::Texture)
				{
					model->GetShader()->SetUniformInt("u_Texture", 0);
					entity->GetMaterial()->GetTexture()->Bind(0);
				}
				model->GetShader()->SetUniformMat4("u_Model", entity->GetModelMatrix());
				model->Render();
			}
			model->GetShader()->Unbind();
			model->GetVertexArray()->GetIndexBuffer()->Unbind();
			model->GetVertexArray()->Unbind();
		}
	}
}