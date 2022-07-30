#pragma once

#include "Core.h"
#include <variant>

namespace Moon
{
	typedef std::function<void()>								StartCallback;
	typedef std::function<void()>								UpdateCallback;
	typedef std::function<void()>								CloseCallback;
	typedef std::function<void(const String&)>					KeyPressCallback;
	typedef std::function<void(const String&)>					KeyReleaseCallback;
	typedef std::function<void(const String&)>					KeyRepeatCallback;
	typedef std::function<void(Vec2, ButtonType, ButtonAction)> ClickCallback;
	typedef std::function<void(Vec2)>							MouseMoveCallback;

	typedef std::function<bool()>								StartConditionCallback;
	typedef std::function<bool()>								UpdateConditionCallback;
	typedef std::function<bool()>								CloseConditionCallback;
	typedef std::function<bool(const String&)>					KeyPressConditionCallback;
	typedef std::function<bool(const String&)>					KeyReleaseConditionCallback;
	typedef std::function<bool(const String&)>					KeyRepeatConditionCallback;
	typedef std::function<bool(Vec2, ButtonType, ButtonAction)> ClickConditionCallback;
	typedef std::function<bool(Vec2)>							MouseMoveConditionCallback;

	typedef std::variant<StartConditionCallback, KeyPressConditionCallback, ClickConditionCallback, MouseMoveConditionCallback> EventCallback;

	class MOON_API ClassEventController
	{
	public:
		virtual void OnStart() {};
		virtual void OnUpdate() {};
		virtual void OnClose() {};
		virtual void OnKeyPress(const String& key) {};
		virtual void OnKeyRelease(const String& key) {};
		virtual void OnKeyRepeat(const String& key) {};
		virtual void OnClick(Vec2, ButtonType, ButtonAction) {};
		virtual void OnMouseMove(Vec2) {};
	};

	class CallbackEventController
	{
	public:
		MOON_API inline void OnStart(StartCallback callback)				{ m_StartCallback		= callback;	}
		MOON_API inline void OnUpdate(UpdateCallback callback)				{ m_UpdateCallback		= callback;	}
		MOON_API inline void OnClose(CloseCallback callback)				{ m_CloseCallback		= callback;	}
		MOON_API inline void OnKeyPress(KeyPressCallback callback)			{ m_KeyPressCallback	= callback;	}
		MOON_API inline void OnKeyRelease(KeyReleaseCallback callback)		{ m_KeyReleaseCallback	= callback;	}
		MOON_API inline void OnKeyRepeat(KeyRepeatCallback callback)		{ m_KeyRepeatCallback	= callback;	}
		MOON_API inline void OnClick(ClickCallback callback)				{ m_ClickCallback		= callback; }
		MOON_API inline void OnMouseMove(MouseMoveCallback callback)		{ m_MouseMoveCallback	= callback;	}
		MOON_API inline void AddChildCallback(CallbackEventController* cec, EventType et, EventCallback ec)
		{
			m_ChildCallbacks[et].push_back(std::pair<CallbackEventController*, EventCallback>(cec, ec));
		}
		MOON_API void Start();
		MOON_API void Update();
		MOON_API void Close();
		MOON_API void KeyPress(const String& key);
		MOON_API void KeyRelease(const String& key);
		MOON_API void KeyRepeat(const String& key);
		MOON_API void Click(Vec2 pos, ButtonType bt, ButtonAction ba);
		MOON_API void MouseMove(Vec2 pos);
	private:
		StartCallback m_StartCallback = nullptr;
		UpdateCallback m_UpdateCallback = nullptr;
		CloseCallback m_CloseCallback = nullptr;
		KeyPressCallback m_KeyPressCallback = nullptr;
		KeyReleaseCallback m_KeyReleaseCallback = nullptr;
		KeyRepeatCallback m_KeyRepeatCallback = nullptr;
		ClickCallback m_ClickCallback = nullptr;
		MouseMoveCallback m_MouseMoveCallback = nullptr;
		HashMap<EventType, List<Pair<CallbackEventController*, EventCallback>>> m_ChildCallbacks;
	};
}
