#include <climits>
#include <random>

using namespace std;

class Random
{
    private:
        int LIST_SIZE;
        random_device rd;
        mt19937_64 randomEngine;

    public:
        Random();
        Random(int listSize);
        int randInteger();
        unsigned long long randLongLong();
        int randBinary();
        double randUniform();
};