#include "Event.hpp"

namespace Moon
{
	std::queue<Event*> EventHandler::s_EventQueue;
	List<CustomEvent*> EventHandler::s_CustomEvents;
	HashMap<String, bool> EventHandler::s_Keys;
	SortedMap<ButtonType, Bool> EventHandler::s_MouseButtons;
	void* EventHandler::s_MouseMoveApp;
	void* EventHandler::s_ClickApp;

	Event::Event(EventType type, EventData data) : m_EventType(type), m_EventData(data)
	{
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, void* app) : m_Callback(callback), m_Interval(ms), m_Application(app), m_OneTime(false)
	{
		ResetTime();
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, void* app, Bool oneTime) : m_Callback(callback), m_Interval(ms), m_Application(app), m_OneTime(oneTime)
	{
		ResetTime();
	}

	void CustomEvent::ResetTime()
	{
		m_PrevTime = Util::CurrentTime();
	}

	Event* EventHandler::Front()
	{
		if (s_EventQueue.size() == 0) return nullptr;
		return s_EventQueue.front();
	}

	void EventHandler::Pop()
	{
		delete s_EventQueue.front()->GetEventData();
		s_EventQueue.pop();
	}

	void EventHandler::Push(Event* e)
	{
		EventType eventType = e->GetEventType();
		if (eventType == EventType::KeyPress)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = true;
		}
		else if (eventType == EventType::KeyRelease)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = false;
		}
		else if (eventType == EventType::Click)
		{
			ClickData data = *(static_cast<ClickData*>(e->GetEventData()));
			s_MouseButtons[data.Type] = data.Action == ButtonAction::Press;
		}
		s_EventQueue.push(e);
	}

	void EventHandler::Push(CustomEvent* e)
	{
		s_CustomEvents.push_back(e);
	}

	Bool EventHandler::KeyDown(const Char* key)
	{
		return s_Keys[key];
	}

	Bool EventHandler::MouseButtonDown(ButtonType bt)
	{
		return s_MouseButtons[bt];
	}

	void EventHandler::Update()
	{
		List<CustomEvent*> rem;

		for (Uint i = 0; i < s_CustomEvents.size(); i++)
		{
			CustomEvent* e = s_CustomEvents[i];
			if ((Util::CurrentTime() - e->GetPrevTime()).count() >= e->GetInterval())
			{
				e->ResetTime();
				e->GetCallback()(e->GetApplication());
				if (e->GetOneTime())
				{
					rem.push_back(e);
				}
			}
		}

		for (CustomEvent*& e : rem)
		{
			s_CustomEvents.erase(std::remove(s_CustomEvents.begin(), s_CustomEvents.end(), e), s_CustomEvents.end());
		}
	}
}