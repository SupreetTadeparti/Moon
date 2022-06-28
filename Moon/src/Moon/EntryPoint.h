#pragma once

#ifdef MOON_PLATFORM_WINDOWS

extern Moon::Application* Moon::CreateApplication();

int main(int argc, char** argv)
{
	Moon::Logger::Init();

	auto app = Moon::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif