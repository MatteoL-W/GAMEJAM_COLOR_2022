#pragma once

#include <chrono>
#include <iostream>
#include <random>

std::mt19937 newGenerator();

/**
 * @brief Returns a random number between min and max, uniform distribution
 * @param min
 * @param max
 * @return
 */

template<typename T, typename P>
T randomUniformDistribution(const T min, const P max)
{
    std::mt19937                      generator = newGenerator();
    std::uniform_real_distribution<T> uniformRealDistribution(min, max);
    return uniformRealDistribution(generator);
}

template<>
int randomUniformDistribution<int>(int min, int max);

/**
 * @brief Returns a random number according to normal distribution
 * @param mean
 * @param stdev
 * @return
 */

template<typename T, typename P>
T randomNormalDistribution(const T mean, const P stdev)
{
    std::mt19937                generator = newGenerator();
    std::normal_distribution<T> normalDistribution(mean, stdev);
    return normalDistribution(generator);
}

/**
 * @brief Returns a random number according to poisson distribution
 * @param lambda
 * @return
 */

template<typename T>
T randomPoissonDistribution(const T lambda)
{
    std::mt19937                generator = newGenerator();
    std::poisson_distribution<> poissonDistribution(lambda);
    return poissonDistribution(generator);
}

/**
 * @brief Returns bool which has probability p of being true
 * @param p probability of true
 * @return
 */

template<typename T>
bool randomBernoulliDistribution(const T p)
{
    std::mt19937                generator = newGenerator();
    std::bernoulli_distribution bernoulliDistribution(p);
    return bernoulliDistribution(generator);
}