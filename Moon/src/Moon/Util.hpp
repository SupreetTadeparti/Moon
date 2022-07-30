#pragma once

#include "Core.h"

namespace Moon
{
	namespace Util
	{
		using namespace std::chrono;
		MOON_API Int Random(Int start, Int end);
		MOON_API milliseconds CurrentTime();
	}
}