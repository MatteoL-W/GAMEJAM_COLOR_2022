#include "../include/Random.hpp"

/**
 * @brief Returns a generator for random purpose
 * @return
 */

std::mt19937 newGenerator()
{
    unsigned     seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    return generator;
}

template<>
int randomUniformDistribution<int>(const int min, const int max)
{
    std::mt19937                       generator = newGenerator();
    std::uniform_int_distribution<int> uniformRealDistribution(min, max);
    return uniformRealDistribution(generator);
}