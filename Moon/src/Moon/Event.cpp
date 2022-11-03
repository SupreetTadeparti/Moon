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

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms) : m_Callback(callback), m_Interval(ms), m_OneTime(false)
	{
		ResetTime();
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, Bool oneTime) : m_Callback(callback), m_Interval(ms), m_OneTime(oneTime)
	{
		ResetTime();
	}

	void CustomEvent::Invoke()
	{
		std::invoke(m_Callback);
	}

	void CustomEvent::ResetTime()
	{
		m_PrevTime = Util::Time::CurrentTime(Util::TimeUnit::Millisecond);
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

	void EventHandler::Add(Event* e)
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

	void EventHandler::AddCustomEvent(CustomEvent* e)
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
			Uint prevTime = e->GetPrevTime();
			Uint currTime = Util::Time::CurrentTime(Util::TimeUnit::Millisecond);
			if (currTime - prevTime >= e->GetInterval())
			{
				e->ResetTime();
				e->Invoke();
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