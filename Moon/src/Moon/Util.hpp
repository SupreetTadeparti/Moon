#pragma once

#include "Core.h"

namespace Moon
{
	namespace Util
	{
		using namespace std::chrono;

		enum class TimeUnit
		{
			Microsecond,
			Millisecond,
			Second,
		};

		class Random
		{
		public:
			template <class T>
			static MOON_API T Choice(List<T> list);
			MOON_API static Int Range(Int start, Int end);
		};

		class Time
		{
		public:
			MOON_API static Uint CurrentTime(TimeUnit=TimeUnit::Second);
		};
	}
}