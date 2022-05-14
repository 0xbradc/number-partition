#include "Random.h"

Random::Random()
{
    LIST_SIZE = 100;
    std::random_device rd;
    std::mt19937_64 randomEngine(rd());
}

Random::Random(int listSize)
{
    LIST_SIZE = listSize;
    std::random_device rd;
    std::mt19937_64 randomEngine(rd());
}

int Random::randInteger()
{
    uniform_int_distribution<int> randIntegerDist(1, LIST_SIZE - 1);
    return randIntegerDist(randomEngine);
}

unsigned long long Random::randLongLong()
{
    uniform_int_distribution<unsigned long long> randLongLongDist(1, pow(10, 12));
    return randLongLongDist(randomEngine);
}

int Random::randBinary()
{
    uniform_int_distribution<int> randBinaryDist(0, 1);
    return randBinaryDist(randomEngine);
}

double Random::randUniform()
{
    uniform_real_distribution<double> randUniformDist(0, 1);
    return randUniformDist(randomEngine);
}
