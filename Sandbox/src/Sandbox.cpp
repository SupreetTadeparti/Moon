#include <Moon.h>

using namespace Moon;

// Example App
class Sandbox : public Application
{
public:
	Entity* square;

	Sandbox() : square(nullptr)
	{
		Window::SetDimensions(1280, 720);
		Renderer::SetFOV(70);
		Renderer::SetRenderType(RenderType::ThreeD);
		Renderer::SetBackgroundColor(Vec3(200, 200, 200));
	}

	void OnStart()
	{
		Scene* scene = new Scene();
		Model* squareModel = new Model(VertexArray::DefaultRect(), new Material(new Color(Vec4(100, 100, 100, 1))));
		square = new Entity(squareModel, Vec3(0, 0, -10));
		scene->AddEntity(square);
	
		Renderer::SetScene(scene);
	}

	void OnUpdate()
	{
		square->Rotate(Vec3(0, 0, 0.001));
	}
};

Application* Moon::CreateApplication()
{
	return new Sandbox();
}