#include "Util.hpp"
#include "Material.hpp"

namespace Moon
{
    namespace Util
    {
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

        template MOON_API Int Random::Choice(List<Int>);
        template MOON_API Double Random::Choice(List<Double>);
        template MOON_API Float Random::Choice(List<Float>);
        template MOON_API Material* Random::Choice(List<Material*>);
    }
}