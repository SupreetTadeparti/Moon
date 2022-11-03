#pragma once

#include "EventController.hpp"

namespace Moon
{
	class MOON_API Application : public ClassEventController
	{
	public:
		void Run();
		void Close();
		inline Uint GetFrames() const { return m_Frames; }
	private:
		Uint m_Frames = 0;
	};

	Application* CreateApplication();
}
