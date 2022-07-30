#include <Moon.h>

using namespace Moon;

class Sandbox : public Application
{
public:
};

Application* Moon::CreateApplication()
{
	return new Sandbox();
}