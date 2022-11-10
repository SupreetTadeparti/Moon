#include "Renderer.hpp"

namespace Moon
{
	Scene* Renderer::s_Scene = nullptr;
	Double Renderer::s_FOV = 70.0f;
	RenderType Renderer::s_RenderType = RenderType::ThreeD;
	Vec3 Renderer::s_BackgroundColor(0.7f);
	Bool Renderer::s_Wireframe(false);

	void Renderer::Update()
	{
		s_Scene->Update();
		s_Scene->UpdateModels();
	}

	void Renderer::SetScene(Scene* scene)
	{
		s_Scene = scene;
	}

	void Renderer::ToggleWireframe()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE + s_Wireframe);
		s_Wireframe = !s_Wireframe;
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
				model->GetShader()->SetView(s_Scene->GetCamera()->GetViewMatrix());
			}
			Material* material = model->GetMaterial();
			switch (material->GetMaterialType())
			{
			case MaterialType::Color:
				model->GetShader()->SetUniformInt("u_FragmentType", 1);
				model->GetShader()->SetUniformVec4("u_Color", material->GetColor()->GetColor());
				break;
			case MaterialType::Texture:
				model->GetShader()->SetUniformInt("u_FragmentType", 2);
				model->GetShader()->SetUniformInt("u_Texture", 0);
				material->GetTexture()->Bind(0);
				break;
			}
			Bool ambientLight = s_Scene->GetAmbientLight() != nullptr;
			model->GetShader()->SetUniformInt("u_AmbientLightActivated", ambientLight);
			if (ambientLight)
			{
				model->GetShader()->SetUniformVec3("u_AmbientLightColor", s_Scene->GetAmbientLight()->GetColor() / 255.0f);
				model->GetShader()->SetUniformFloat("u_AmbientLightBrightness", s_Scene->GetAmbientLight()->GetBrightness());
			}
			Bool directionalLight = s_Scene->GetDirectionalLight() != nullptr;
			model->GetShader()->SetUniformInt("u_DirectionalLightActivated", directionalLight);
			if (directionalLight)
			{
				model->GetShader()->SetUniformVec3("u_DirectionalLightColor", s_Scene->GetDirectionalLight()->GetColor() / 255.0f);
				model->GetShader()->SetUniformVec3("u_DirectionalLightDirection", s_Scene->GetDirectionalLight()->GetDirection());
			}
			model->GetShader()->SetUniformInt("u_Fixed", model->GetFixed());
			model->Render(s_Scene->GetEntities()[model].first.size());
			model->GetVertexArray()->Unbind();
			model->GetVertexArray()->GetIndexBuffer()->Unbind();
			model->GetShader()->Unbind();
		}
	}
}