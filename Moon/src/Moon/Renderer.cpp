#include "Renderer.hpp"

namespace Moon
{
	Scene* Renderer::s_Scene = nullptr;
	Double Renderer::s_FOV = 70.0f;
	RenderType Renderer::s_RenderType = RenderType::ThreeD;
	Vec3 Renderer::s_BackgroundColor(0.7f);

	void Renderer::Update()
	{
		//s_Scene->UpdateCallback();
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
		for (Model* model : s_Scene->GetModels())
		{
			model->GetVertexArray()->Bind();
			model->GetVertexArray()->GetIndexBuffer()->Bind();
			model->GetShader()->Bind();
			if (s_Scene->GetCamera() != nullptr)
			{
				model->GetShader()->Bind();
				model->GetShader()->SetView(s_Scene->GetCamera()->GetViewMatrix());
			}
			List<Entity*> entities = s_Scene->GetEntities()[model];
			for (Entity* entity : entities)
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