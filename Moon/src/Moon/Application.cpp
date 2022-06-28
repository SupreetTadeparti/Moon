#include "Application.hpp"

namespace Moon
{
	void Application::Run()
	{
		bool running = true;
		OnStart();
		while (running)
		{
			OnUpdate();
			while (EventHandler::Front() != nullptr)
			{
				if (EventHandler::Front()->GetEventType() == EventType::WindowClose)
				{
					running = false;
				}
				EventHandler::Pop();
			}
		}
	}
}