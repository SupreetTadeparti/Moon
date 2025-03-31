#include "Util.hpp"
#include "Entity.hpp"
#include "Material.hpp"

namespace Moon
{
    namespace Util
    {
        template <typename T>
        void Swap(T* a, T* b)
        {
            T temp = *a;
            *a = *b;
            *b = temp;
        }

        template<typename T>
        List<T>* ConcatLists(const std::initializer_list<List<T>*>& lists)
        {
            List<T>* res = new List<T>();

			for (const auto& list : lists)
			{
				res->insert(res->end(), list->begin(), list->end());
			}

            return res;
        }

        template <typename T>
        T Random::Choice(List<T> list)
        {
           return list[Range(0, list.size() - 1)];
        }

        Int Random::Range(Int start, Int end)
        {
            std::mt19937_64 rng;
            uint64_t timeSeed = high_resolution_clock::now().time_since_epoch().count();
            std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
            rng.seed(ss);
            std::uniform_int_distribution<> unif(start, end);
            return unif(rng);
        }

        Uint Time::CurrentTime(TimeUnit tu)
        {
            switch (tu)
            {
            case TimeUnit::Microsecond:
                return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            case TimeUnit::Millisecond:
                return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            default: // Second
                return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
            }
        }

        template <typename T, typename U>
        void Sorter::Sort(List<T> a, List<U> b, std::function<bool(T, T)> cmp)
        {
            if (a.size() != b.size())
            {
                MoonLogError("Size of Lists Must Be Equal!");
            }

            if (a.size() < MAX_BUBBLESORT)
            {
                BubbleSort(a, b, cmp);
            }
            else
            {
                QuickSort(a, b, cmp, 0, a.size() - 1);
            }
        }

        template <typename T, typename U>
        void Sorter::BubbleSort(List<T> a, List<U> b, std::function<bool(T, T)> cmp)
        {
            for (Int i = 0; i < a.size() - 1; i++)
            {
                for (Int j = 0; j < a.size() - i - 1; j++)
                {
                    if (cmp(a[j], a[j + 1]))
                    {
                        Swap(&a[j], &a[j + 1]);
                    }
                }
            }
        }

        template <typename T, typename U>
        void Sorter::QuickSort(List<T> a, List<U> b, std::function<bool(T, T)> cmp, Int low, Int high) {
            if (low < high)
            {
                Int pi = Partition(a, b, cmp, low, high);
                QuickSort(a, b, cmp, low, pi - 1);
                QuickSort(a, b, cmp, pi + 1, high);
            }
        }

        template <typename T, typename U>
        Int Sorter::Partition(List<T> a, List<U> b, std::function<bool(T, T)> cmp, Int low, Int high) {
            T pivot = a[high];
            Int i = low - 1;
            for (Int j = low; j < high; j++)
            {
                if (cmp(a[j], pivot))
                {
                    Swap(&a[++i], &a[j]);
                }
            }
            Swap(&a[i + 1], &a[high]);
            return i + 1;
        }

        template MOON_API Int Random::Choice(List<Int>);
        template MOON_API Double Random::Choice(List<Double>);
        template MOON_API Float Random::Choice(List<Float>);
        template MOON_API Material* Random::Choice(List<Material*>);
        template MOON_API void Sorter::Sort(List<Entity*>, List<Mat4>, std::function<Bool(Entity*, Entity*)> cmp);
        template MOON_API void Sorter::QuickSort(List<Entity*>, List<Mat4>, std::function<Bool(Entity*, Entity*)> cmp, Int, Int);
        template MOON_API void Sorter::BubbleSort(List<Entity*>, List<Mat4>, std::function<Bool(Entity*, Entity*)> cmp);
        template MOON_API void Swap(Int*, Int*);
        template MOON_API void Swap(Double*, Double*);
        template MOON_API void Swap(Entity*, Entity*);
        template MOON_API void Swap(Mat4*, Mat4*);
        template List<Uint>* ConcatLists(const std::initializer_list<List<Uint>*>& lists);
        template List<Float>* ConcatLists(const std::initializer_list<List<Float>*>& lists);
    }
}