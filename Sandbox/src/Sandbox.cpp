#include <Moon.h>

class Sandbox : public Moon::Application
{
public:
	Sandbox()
	{
	}

	void OnStart()
	{

	}

	void OnUpdate()
	{

	}
};

Moon::Application* Moon::CreateApplication()
{
	return new Sandbox();
}

