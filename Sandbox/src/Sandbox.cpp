#include <Moon.h>

using namespace Moon;

class Sandbox : public Application
{
public:
	List<Entity*> entities;
	Uint frames;
	Model* model;
	Scene* scene;

	Sandbox() : scene(nullptr), frames(0), model(nullptr)
	{
		Window::SetDimensions(1280, 720);
		Renderer::SetFOV(70);
		Renderer::SetRenderType(RenderType::ThreeD);
		Renderer::SetBackgroundColor(Vec3(200, 200, 200));
	}

	void OnStart()
	{
		scene = new Scene();
		model = new Model(VertexArray::DefaultBox(), new Material(new Color(Vec4(255, 0, 0, 0.25))));

		scene->SetAmbientLight(new AmbientLight(0.2));
		scene->SetDirectionalLight(new DirectionalLight(Vec3(0.6, 0.7, 0.5)));

		Camera* camera = new Camera();
		FirstPersonCamera* fpc = new FirstPersonCamera(camera);
		fpc->SetSpeed(0.1);
		scene->SetCameraController(fpc);
		
		for (int i = 0; i < 10; i++)
		{
			Int r = Util::Random::Range(0, 255);
			Int g = Util::Random::Range(0, 255);
			Int b = Util::Random::Range(0, 255);
			Model* model = new Model(VertexArray::DefaultBox(), new Material(new Color(Vec4(r, g, b, 1))));
			for (Int j = 0; j < 100; j++)
			{
				Int x = Util::Random::Range(-100, 100);
				Int y = Util::Random::Range(-100, 100);
				Int z = Util::Random::Range(-100, 100);
				Entity* entity = new Entity(model, Vec3(x, y, z), Vec3(), Vec3(3, 5, 3));
				entities.push_back(entity);
				scene->AddEntity(entity);
			}
		}

		Renderer::SetScene(scene);

		EventHandler::AddCustomEvent(new CustomEvent(std::bind(&Sandbox::OnSecond, this), 1000));
	}

	void OnKeyPress(const String& key)
	{
		if (key == "p")
		{
			Renderer::ToggleWireframe();
		}
	}

	void OnSecond()
	{
		LogInfo("FPS: " + std::to_string(frames));
		frames = 0;
	}

	void OnUpdate()
	{
		frames++;
	}
};

Application* Moon::CreateApplication()
{
	return new Sandbox();
}