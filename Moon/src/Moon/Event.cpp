#include "Event.hpp"

namespace Moon
{
	std::vector<CustomEvent*> EventHandler::s_CustomEvents;
	std::queue<Event*> EventHandler::s_EventQueue;
	std::unordered_map<String, bool> EventHandler::s_Keys;

	Event::Event(EventType type, EventData data) : m_EventType(type), m_EventData(data)
	{
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, void* app) : m_Callback(callback), m_Interval(ms), m_Application(app)
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
		if (e->GetEventType() == EventType::KeyDown)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = true;
		}
		else if (e->GetEventType() == EventType::KeyUp)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = false;
		}
		s_EventQueue.push(e);
	}

	void EventHandler::Push(CustomEvent* e)
	{
		s_CustomEvents.push_back(e);
	}

	bool EventHandler::KeyDown(const char* key)
	{
		return s_Keys[key];
	}

	void EventHandler::Update()
	{
		for (CustomEvent* e : s_CustomEvents)
		{
			std::chrono::milliseconds now = Util::CurrentTime();
			if ((now - e->GetPrevTime()).count() >= e->GetInterval())
			{
				e->ResetTime();
				e->GetCallback()(e->GetApplication());
			}
		}
	}
}