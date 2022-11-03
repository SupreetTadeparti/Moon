#include <Moon.h>

using namespace Moon;

class Sandbox : public Application
{
public:
	Camera* camera;
	Scene* scene;
	Model* balloonModel;
	Model* needleModel;
	List<Material*> materials;
	List<Entity*> balloonEntities;
	List<Entity*> needleEntities;
	List<Vec3> needleTrajectories;
	Double cameraVel;

	Sandbox()
	{
		cameraVel = 0;
		Window::SetDimensions(1280, 720);
		Renderer::SetFOV(70);
		Renderer::SetRenderType(RenderType::ThreeD);
		Renderer::SetBackgroundColor(Vec3(60, 90, 200));
	}

	void OnStart()
	{
		materials.push_back(new Material(new Color(245, 10, 10, 0.5)));
		materials.push_back(new Material(new Color(10, 245, 10, 0.5)));
		materials.push_back(new Material(new Color(10, 10, 245, 0.5)));

		Model* gun = ModelLoader::LoadModel("crossbow.obj", new Material(new Color(Vec4(0, 0, 100, 1.0))));
		needleModel = ModelLoader::LoadModel("needle.obj", new Material(new Color(Vec4(100, 0, 0, 1.0))));
		Model* crosshair = new Model(Shape::Rect);
		Model* spacePanel = new Model(Shape::Box);
		//Text* scoreText = new Text(50, 50, "Score: ", "arial", 30);
		balloonModel = new Model(Shape::Sphere);

		crosshair->SetMaterial(new Material(new Color(Vec4(255, 255, 255, 1))));

		spacePanel->SetMaterial(new Material(new Color(Vec4(100, 100, 100, 0.25))));
		
		camera = new Camera();
		FirstPersonCamera* cc = new FirstPersonCamera(camera);
		cc->SetSpeed(0.05);
		
		Entity* gunEntity = new Entity(gun, Vec3(0.0f, -1.f, -2.0f), Vec3(Math::Radians(-90.0), 0, Math::Radians(90.0)), Vec3(0.1, 0.1, 0.1));
		Entity* spaceEntity = new Entity(spacePanel, Vec3(0, 50, 0), Vec3(), Vec3(100, 1, 100));
		Entity* crosshairHorizontalEntity = new Entity(crosshair, Vec3(0, 0, -1), Vec3(), Vec3(0.05, 0.005, 1));
		Entity* crosshairVerticalEntity = new Entity(crosshair, Vec3(0, 0, -1), Vec3(), Vec3(0.005, 0.05, 1));
		crosshairHorizontalEntity->SetFixed(true);
		crosshairVerticalEntity->SetFixed(true);

		gunEntity->SetFixed(true);
		
		scene = new Scene();
		scene->SetCamera(camera);
		scene->SetCameraController(cc);
		scene->SetAmbientLight(new AmbientLight(0.2f));
		scene->SetDirectionalLight(new DirectionalLight(Vec3(0.75, 0.5, -1.0)));
		scene->AddEntity(spaceEntity);
		scene->AddEntity(gunEntity);
		scene->AddEntity(crosshairHorizontalEntity);
		scene->AddEntity(crosshairVerticalEntity);
		//scene->AddText(scoreText);
		Renderer::SetScene(scene);
		EventHandler::AddCustomEvent(new CustomEvent(std::bind(&Sandbox::OnCreateBalloon, this), 1000));

		Audio::Play("theme.mp3");
	}

	void OnClick(Vec2 position, ButtonType bt, ButtonAction ba)
	{
		if (bt == ButtonType::LeftButton && ba == ButtonAction::Press)
		{
			Vec3 position = camera->GetPosition();
			Vec3 rot = camera->GetRotation();
			Double x = camera->GetViewMatrix()[0][2];
			Double y = camera->GetViewMatrix()[1][2];
			Double z = camera->GetViewMatrix()[2][2];
			position.y -= 0.1;
			Entity* needleEntity = new Entity(needleModel, position);
			needleTrajectories.push_back(-Vec3(x, y, z));
			auto yaw = glm::angleAxis(-rot.x + (float)Math::Radians(90), Vec3(1, 0, 0));
			auto pitch = glm::angleAxis(-rot.y, Vec3(0, 1, 0));
			auto rotMat = glm::mat4_cast(pitch * yaw);
			needleEntity->SetRotationMatrix(rotMat);
			needleEntities.push_back(needleEntity);
			scene->AddEntity(needleEntity);
		}
	}

	void OnCreateBalloon()
	{
		// Display FPS
		LogInfo("FPS: " + std::to_string(GetFrames()));

		// Create Balloon
		Int x = Util::Random::Range(-50, 50);
		Int z = Util::Random::Range(-50, 50);
		Entity* balloonEntity = new Entity(balloonModel, Vec3(x, -100, z));
		balloonEntity->SetMaterial(Util::Random::Choice(materials));
		scene->AddEntity(balloonEntity);
		balloonEntities.push_back(balloonEntity);
	}

	void OnKeyPress(const String& key)
	{
		if (key == " ") cameraVel = 0.08;
	}

	void OnUpdate()
	{
		Uint i = 0;
		while (i < balloonEntities.size())
		{
			balloonEntities[i]->Move(Vec3(0, 0.01, 0));
			if (balloonEntities[i]->GetPosition().y > 50)
			{
				scene->RemoveEntity(balloonEntities[i]);
				balloonEntities.erase(std::remove(balloonEntities.begin(), balloonEntities.end(), balloonEntities[i]), balloonEntities.end());
			}
			i++;
		}
		for (Uint i = 0; i < needleEntities.size(); i++)
		{
			Entity* needle = needleEntities[i];
			Vec3 trajectory = needleTrajectories[i];
			Float trajectorySpeed = 0.2;
			needle->Move(trajectory * trajectorySpeed);
			Uint j = 0;
			while (j < balloonEntities.size())
			{
				if (glm::distance(balloonEntities[j]->GetPosition(), needle->GetPosition()) < 2.5f)
				{
					scene->RemoveEntity(balloonEntities[j]);
					balloonEntities.erase(std::remove(balloonEntities.begin(), balloonEntities.end(), balloonEntities[j]), balloonEntities.end());
				}
				j++;
			}
		}
		cameraVel -= 0.0001;
		camera->Move(Vec3(0, cameraVel, 0));
	}
};

Application* Moon::CreateApplication()
{
	return new Sandbox();
}