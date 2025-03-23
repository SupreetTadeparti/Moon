#pragma once

#ifdef MOON_PLATFORM_WINDOWS

extern Moon::Application* Moon::CreateApplication();

int main(int argc, char** argv)
{
	/* Initialize Components */
	Moon::Logger::Init();
	Moon::Text::Init();
	Moon::Geometry::Init();

	if (Moon::Window::Init() == -1)
	{
		MoonLogCritical("Failed to Initialize GLFW!");
		return -1;
	}

	auto app = Moon::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif