#include "Application.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"


namespace Moon
{
	void Application::Run()
	{
		int err = Window::Create();

		if (err == -1)
		{
			MoonLogCritical("Failed to Initialize Window!");
			return;
		}

		if (err == -2)
		{
			MoonLogCritical("Failed to Initialize GlEW!");
			return;
		}

		bool running = true;

		MoonLogInfo("Started");

		OnStart();

		MoonLogInfo("Running");

		while (running)
		{
			OnUpdate();
			Renderer::Update();
			Renderer::GetScene()->Update();
			Renderer::Prepare();
			Renderer::Render();
			EventHandler::Update();
			Window::Update();
			while (EventHandler::Front() != nullptr)
			{
				Event* e = EventHandler::Front();
				switch (e->GetEventType())
				{
				case EventType::WindowClose:
					OnClose();
					Renderer::GetScene()->Close();
					running = false;
					break;
				case EventType::KeyPress:
					OnKeyPress(*(static_cast<String*>(e->GetEventData())));
					Renderer::GetScene()->KeyPress(*(static_cast<String*>(e->GetEventData())));
					break;
				case EventType::KeyRelease:
					OnKeyRelease(*(static_cast<String*>(e->GetEventData())));
					Renderer::GetScene()->KeyRelease(*(static_cast<String*>(e->GetEventData())));
					break;
				case EventType::KeyRepeat:
					OnKeyRepeat(*(static_cast<String*>(e->GetEventData())));
					Renderer::GetScene()->KeyRepeat(*(static_cast<String*>(e->GetEventData())));
					break;
				case EventType::Click:
					ClickData data = *(static_cast<ClickData*>(e->GetEventData()));
					OnClick(data.Position, data.Type, data.Action);
					Renderer::GetScene()->Click(data.Position, data.Type, data.Action);
					break;
				case EventType::MouseMove:
					OnMouseMove(*(static_cast<Vec2*>(e->GetEventData())));
					Renderer::GetScene()->MouseMove(*(static_cast<Vec2*>(e->GetEventData())));
					break;
				}
				EventHandler::Pop();
			}
		}

		Window::Close();
	}

	void Application::Close()
	{
		EventHandler::Push(new Event(EventType::WindowClose, nullptr));
	}
}