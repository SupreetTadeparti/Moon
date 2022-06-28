#include <Moon.h>

class Sandbox : public Moon::Application
{
public:
	void OnStart()
	{
		LogInfo("Started");
	}

	void OnUpdate()
	{
		LogInfo("Updated");
	}
};

Moon::Application* Moon::CreateApplication()
{
	return new Sandbox();
}