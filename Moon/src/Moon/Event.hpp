#pragma once

#include "Core.h"
#include <queue>
#include <unordered_map>

namespace Moon
{
	typedef void* EventData;
	typedef void (*CustomEventCallback) (void*);

	enum class ButtonType;

	enum class MOON_API EventType
	{
		Start, Update,
		WindowClose, WindowResize,
		Click, MouseMove,
		KeyPress, KeyRelease, KeyRepeat
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

	class CustomEvent
	{
	public:
		MOON_API CustomEvent(CustomEventCallback callback, Uint ms, void* app);
		MOON_API CustomEvent(CustomEventCallback callback, Uint ms, void* app, Bool oneTime);
		MOON_API void ResetTime();
		MOON_API inline Bool GetOneTime() const { return m_OneTime; }
		MOON_API inline Uint GetInterval() const { return m_Interval; }
		MOON_API inline void* GetApplication() const { return m_Application; }
		MOON_API inline CustomEventCallback GetCallback() const { return m_Callback; }
		MOON_API inline std::chrono::milliseconds GetPrevTime() const { return m_PrevTime; }
	private:
		CustomEventCallback m_Callback;
		Uint m_Interval;
		std::chrono::milliseconds m_PrevTime;
		void* m_Application;
		Bool m_OneTime;
	};

	class EventHandler
	{
	public:
		MOON_API static Event* Front();
		MOON_API static void Push(Event* e);
		MOON_API static void Push(CustomEvent* e);
		MOON_API static void Pop();
		MOON_API static void Update();
		MOON_API static Bool KeyDown(const Char* key);
		MOON_API static Bool MouseButtonDown(ButtonType bt);
	private:
		static std::queue<Event*> s_EventQueue;
		static HashMap<String, Bool> s_Keys;
		static SortedMap<ButtonType, Bool> s_MouseButtons;
		static List<CustomEvent*> s_CustomEvents;
		static void* s_MouseMoveApp;
		static void* s_ClickApp;
	};
}