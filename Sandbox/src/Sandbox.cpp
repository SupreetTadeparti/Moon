#include <Moon.h>

using namespace Moon;

class Sandbox : public Application
{
public:
	//List<Entity*> entities;
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

	void GenRandObjects(Uint instances)
	{

		for (Int j = 0; j < instances; j++)
		{
			Int r = Util::Random::Range(0, 255);
			Int g = Util::Random::Range(0, 255);
			Int b = Util::Random::Range(0, 255);

			GeometryType gt = (GeometryType)Util::Random::Range(0, 2);

			model = new Model(new Geometry(gt), new Material(new Color(Vec4(r, g, b, 1))));

			Int x = Util::Random::Range(-100, 100);
			Int y = Util::Random::Range(-100, 100);
			Int z = Util::Random::Range(-100, 100);
			Entity* entity = new Entity(model, Vec3(x, y, z), Vec3(), Vec3(3, 5, 3));
			//entities.push_back(entity);
			scene->AddEntity(entity);
		}
	}

	void OnStart()
	{
		scene = new Scene();

		//scene->SetAmbientLight(new AmbientLight(0.2));
		//scene->SetDirectionalLight(new DirectionalLight(Vec3(0.6, 0.7, 0.5)));

		Camera* camera = new Camera();
		FirstPersonCamera* fpc = new FirstPersonCamera(camera);
		fpc->SetSpeed(0.05);
		scene->SetCameraController(fpc);

		GenRandObjects(100);
		GenRandObjects(100);
		GenRandObjects(100);
		GenRandObjects(100);
		GenRandObjects(100);

		//scene->AddText(new Text(50, 50, "SPELL RUINS", "arial", 48));

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