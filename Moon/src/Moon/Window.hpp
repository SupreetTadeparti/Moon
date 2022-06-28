#pragma once
#include "Core.h"

namespace Moon
{
	class MOON_API Window
	{
	public:
		static void Create(uint32_t width=640, uint32_t height=360, const std::string& title="Moon Application");
		static void Run();
		static void Update();
	private:
		//GLFWwindow* s_Window;
	};
}
