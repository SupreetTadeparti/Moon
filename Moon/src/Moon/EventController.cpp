#include "EventController.hpp"

namespace Moon
{
	void CallbackEventController::Start()
	{
		if (m_StartCallback != nullptr) std::invoke(m_StartCallback);
		for (const auto& controller : m_ChildCallbacks[EventType::Start])
		{
			if (std::invoke(std::get<StartConditionCallback>(controller.second)))
			{
				controller.first->Start();
			}
		}
	}

	void CallbackEventController::Update()
	{
		if (m_UpdateCallback != nullptr) std::invoke(m_UpdateCallback);
		for (const auto& controller : m_ChildCallbacks[EventType::Update])
		{
			if (std::invoke(std::get<UpdateConditionCallback>(controller.second)))
			{
				controller.first->Update();
			}
		}
	}

	void CallbackEventController::Close()
	{
		if (m_CloseCallback != nullptr) std::invoke(m_CloseCallback);
		for (const auto& controller : m_ChildCallbacks[EventType::WindowClose])
		{
			if (std::invoke(std::get<CloseConditionCallback>(controller.second)))
			{
				controller.first->Close();
			}
		}
	}

	void CallbackEventController::KeyPress(const String& key)
	{
		if (m_KeyPressCallback != nullptr) std::invoke(m_KeyPressCallback, key);
		for (const auto& controller : m_ChildCallbacks[EventType::KeyPress])
		{
			if (std::invoke(std::get<KeyPressConditionCallback>(controller.second), key))
			{
				controller.first->KeyPress(key);
			}
		}
	}

	void CallbackEventController::KeyRelease(const String& key)
	{
		if (m_KeyReleaseCallback != nullptr) std::invoke(m_KeyReleaseCallback, key);
		for (const auto& controller : m_ChildCallbacks[EventType::KeyRelease])
		{
			if (std::invoke(std::get<KeyReleaseConditionCallback>(controller.second), key))
			{
				controller.first->KeyRelease(key);
			}
		}
	}

	void CallbackEventController::KeyRepeat(const String& key)
	{
		if (m_KeyRepeatCallback != nullptr) std::invoke(m_KeyRepeatCallback, key);
		for (const auto& controller : m_ChildCallbacks[EventType::KeyRepeat])
		{
			if (std::invoke(std::get<KeyRepeatConditionCallback>(controller.second), key))
			{
				controller.first->KeyRepeat(key);
			}
		}
	}

	void CallbackEventController::Click(Vec2 pos, ButtonType bt, ButtonAction ba)
	{
		if (m_ClickCallback != nullptr) std::invoke(m_ClickCallback, pos, bt, ba);
		for (const auto& controller : m_ChildCallbacks[EventType::Click])
		{
			if (std::invoke(std::get<ClickConditionCallback>(controller.second), pos, bt, ba))
			{
				controller.first->Click(pos, bt, ba);
			}
		}
	}

	void CallbackEventController::MouseMove(Vec2 pos)
	{
		if (m_MouseMoveCallback != nullptr) std::invoke(m_MouseMoveCallback, pos);
		for (const auto& controller : m_ChildCallbacks[EventType::MouseMove])
		{
			if (std::invoke(std::get<MouseMoveConditionCallback>(controller.second), pos))
			{
				controller.first->MouseMove(pos);
			}
		}
	}
}