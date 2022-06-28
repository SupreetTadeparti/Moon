#include "Event.hpp"

namespace Moon
{
	std::queue<Event*> EventHandler::s_EventQueue;

	Event::Event(EventType type, EventData data) : m_EventType(type), m_EventData(data)
	{
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
		s_EventQueue.push(e);
	}
}