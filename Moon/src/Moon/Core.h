#pragma once

#ifdef MOON_PLATFORM_WINDOWS
	#ifdef MOON_BUILD_DLL
		#define MOON_API __declspec(dllexport)
	#else
		#define MOON_API __declspec(dllimport)
	#endif
#else
	#error Moon only supports Windows!
#endif

#include <iostream>
#include "Event.hpp"
#include "Logger.hpp"
