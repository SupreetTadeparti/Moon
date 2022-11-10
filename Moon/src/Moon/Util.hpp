#pragma once

#include "Core.h"

#define MAX_BUBBLESORT 5000

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

		template <typename T>
		MOON_API void Swap(T* a, T* b);

		class Time
		{
		public:
			MOON_API static Uint CurrentTime(TimeUnit=TimeUnit::Second);
		};

		class Random
		{
		public:
			template <class T>
			static MOON_API T Choice(List<T> list);
			MOON_API static Int Range(Int start, Int end);
		};

		class Sorter
		{
		public:	
			template <typename T, typename U>
			MOON_API static void Sort(List<T> a, List<U> b, std::function<Bool(T, T)> cmp);

			template <typename T, typename U>
			MOON_API static void BubbleSort(List<T> a, List<U> b, std::function<Bool(T, T)> cmp);

			template <typename T, typename U>
			MOON_API static void QuickSort(List<T> a, List<U> b, std::function<Bool(T, T)> cmp, Int low, Int high);
		private:
			// Helper Functions

			template <typename T, typename U>
			static Int Partition(List<T> a, List<U> b, std::function<Bool(T, T)> cmp, Int low, Int high);
		};
	}
}