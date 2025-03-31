#include "Renderer.hpp"

namespace Moon
{
	Scene* Renderer::s_Scene(nullptr);
	Double Renderer::s_FOV(70.0f);
	RenderType Renderer::s_RenderType(RenderType::ThreeD);
	Vec3 Renderer::s_BackgroundColor(0.7f);
	Bool Renderer::s_Wireframe(false);
	Bool Renderer::s_Modified(false);

	void Renderer::Update()
	{
		s_Scene->Update();
		if (s_Modified)
		{
			s_Scene->UpdateEntities();
			s_Modified = false;
		}
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
		s_Scene->Render();
	}
}