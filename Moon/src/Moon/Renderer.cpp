#include "Renderer.hpp"

namespace Moon
{
	Scene* Renderer::s_Scene = nullptr;
	Double Renderer::s_FOV = 70.0f;
	RenderType Renderer::s_RenderType = RenderType::ThreeD;
	Vec3 Renderer::s_BackgroundColor(0.7f);

	void Renderer::Update()
	{
		s_Scene->Update();
	}

	void Renderer::Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b, 1.0f);
	}

	void Renderer::RenderEntity(Entity* entity)
	{
		Model* model = entity->GetModel();
		MaterialType materialType = entity->GetMaterial()->GetMaterialType();
		if (materialType == MaterialType::Color)
		{
			model->GetShader()->SetUniformInt("u_FragmentType", 1);
			model->GetShader()->SetUniformVec4("u_Color", entity->GetMaterial()->GetColor()->GetColor());
		}
		else if (materialType == MaterialType::Texture)
		{
			model->GetShader()->SetUniformInt("u_FragmentType", 2);
			model->GetShader()->SetUniformInt("u_Texture", 0);
			entity->GetMaterial()->GetTexture()->Bind(0);
		}
		model->GetShader()->SetUniformInt("u_Fixed", entity->GetFixed());
		model->GetShader()->SetUniformMat4("u_Model", entity->GetModelMatrix());
		model->Render();
	}

	void Renderer::Render()
	{
		for (Model* model : s_Scene->GetModels())
		{
			model->GetVertexArray()->Bind();
			model->GetVertexArray()->GetIndexBuffer()->Bind();
			model->GetShader()->Bind();
			Bool defaultShader = model->GetShader() == Shader::GetDefault();
			if (s_Scene->GetCamera() != nullptr)
			{
				model->GetShader()->SetView(s_Scene->GetCamera()->GetViewMatrix());
			}
			if (defaultShader)
			{
				if (s_Scene->GetAmbientLight() != nullptr)
				{
					model->GetShader()->SetUniformVec3("u_AmbientLightColor", s_Scene->GetAmbientLight()->GetColor() / 255.0f);
					model->GetShader()->SetUniformFloat("u_AmbientLightBrightness", s_Scene->GetAmbientLight()->GetBrightness());
				}
				if (s_Scene->GetDirectionalLight() != nullptr)
				{
					model->GetShader()->SetUniformVec3("u_DirectionalLightColor", s_Scene->GetDirectionalLight()->GetColor() / 255.0f);
					model->GetShader()->SetUniformVec3("u_DirectionalLightDirection", s_Scene->GetDirectionalLight()->GetDirection());
				}
				model->GetShader()->SetUniformInt("u_AmbientLightActivated", s_Scene->GetAmbientLight() != nullptr);
				model->GetShader()->SetUniformInt("u_DirectionalLightActivated", s_Scene->GetDirectionalLight() != nullptr);
			}
			List<Entity*> entities = s_Scene->GetEntities()[model];
			for (Entity* entity : entities)
			{
				RenderEntity(entity);
			}
			List<Entity*> translucentEntities = s_Scene->GetAlphaEntities()[model];
			sort(translucentEntities.begin(), translucentEntities.end(), [](Entity* a, Entity* b) -> bool
				{
					float aDistance = glm::length(s_Scene->GetCamera()->GetPosition() - a->GetPosition());
					float bDistance = glm::length(s_Scene->GetCamera()->GetPosition() - b->GetPosition());
					return aDistance > bDistance;
				});
			for (Entity* entity : translucentEntities)
			{
				RenderEntity(entity);
			}
			model->GetShader()->Unbind();
			model->GetVertexArray()->GetIndexBuffer()->Unbind();
			model->GetVertexArray()->Unbind();
		}
	}
}