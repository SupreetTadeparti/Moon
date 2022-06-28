#pragma once

#include "Core.h"
#include <queue>

namespace Moon
{
	typedef void* EventData;

	enum class MOON_API EventType
	{
		WindowClose, WindowResize,
		MouseLeftPress, MouseLeftRelease,
		MouseRightPress, MouseRightRelease,
		MouseMove,
		KeyDown, KeyUp,
	};

	class MOON_API Event
	{
	public:
		Event(EventType type, EventData data);
		inline EventType GetEventType() { return m_EventType; };
		inline EventData GetEventData() { return m_EventData; };
	private:
		EventType m_EventType;
		EventData m_EventData;
	};

	class EventHandler
	{
	public:
		static MOON_API Event* Front();
		static MOON_API void Push(Event* e);
		static MOON_API void Pop();
	private:
		static std::queue<Event*> s_EventQueue;
	};
}
