#pragma once

#include "EventController.hpp"

namespace Moon
{
	class MOON_API Application : public ClassEventController
	{
	public:
		void Run();
		void Close();
	};

	Application* CreateApplication();
}
