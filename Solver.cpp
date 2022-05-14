#include <climits>
#include <ostream>
#include "Solver.h"

///////////////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////////////
Solver::Solver() {}

Solver::Solver(int alg, double coolFactor)
{
    ALG = alg;
    LIST_SIZE = 100;
    MAX_ITER = 25000;
    list = generateRandomList();
    Random rand = Random(LIST_SIZE);
    coolingFactor = coolFactor;
}

Solver::Solver(int alg, vector<unsigned long long> lst, double coolFactor)
{
    ALG = alg;
    LIST_SIZE = lst.size();
    MAX_ITER = 25000;
    list = lst; // In case we have a predetermined list
    Random rand = Random(LIST_SIZE);    
    coolingFactor = coolFactor;
}

///////////////////////////////////////////////////////////////////////////////
// Getters, Setters, Printers
///////////////////////////////////////////////////////////////////////////////
int Solver::getAlgorithm()
{
    return ALG;
}

vector<unsigned long long> Solver::getList()
{
    return list;
}

void Solver::setList(vector<unsigned long long> lst)
{
    list = lst;
}

void Solver::printList()
{
    cout << "List: " << endl;
    for (unsigned long i = 0; i < list.size(); i++)
        cout << list[i] << endl;
    // cout << list[i] << ", ";
    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////
// Random Generators
///////////////////////////////////////////////////////////////////////////////
vector<unsigned long long> Solver::generateRandomList()
{
    vector<unsigned long long> lst;

    for (int i = 0; i < LIST_SIZE; i++)
        lst.push_back(rand.randLongLong());

    return lst;
}

// Generates a random list of binaries (0s and 1s)
vector<int> Solver::generateBinaryList()
{
    vector<int> lst = vector<int>(LIST_SIZE, 0);

    for (int i = 0; i < LIST_SIZE; i++)
        lst[i] = rand.randBinary();
    return lst;
}

// Generates prepartitioned and summed groups
vector<unsigned long long> Solver::generatePrepartitionedList()
{
    vector<unsigned long long> lst(LIST_SIZE, 0);

    for (int i = 0; i < LIST_SIZE; i++)
    {
        // Generates a random group
        int r = rand.randInteger();
        lst[r] += list[i];
    }

    return lst;
}

vector<int> Solver::generateNeighborOfBinaryList(vector<int> lst)
{
    int i = rand.randInteger();
    lst[i] = !lst[i]; // Flip a random bit

    int j = rand.randInteger();
    while (j == i) // Ensure that i and j are different
        j = rand.randInteger();
    double flipSecond = rand.randUniform();
    if (flipSecond < 0.5)
        lst[j] = !lst[j];

    return lst;
}

vector<unsigned long long> Solver::generateNeighborOfPrepartitionedList(vector<unsigned long long> lst)
{
    // Choose two random indices i and j from [1, n] with p_i \neq j and set p_i to j.
    int i = rand.randInteger();
    int j = rand.randInteger();
    while (lst[i] == j)
        j = rand.randInteger();

    lst[i] = j;
    return lst;
}

///////////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////////
int Solver::cooling(int iter)
{
    return (int)(pow(10.0, 10.0) * coolingFactor * floor(iter / 300));
}

unsigned long long Solver::residue(vector<int> binaryList)
{
    unsigned long long sum1 = 0, sum2 = 0;
    for (unsigned long i = 0; i < binaryList.size(); i++)
        if (binaryList[i] == 0)
            sum1 += list[i];
        else
            sum2 += list[i];

    return (max(sum1, sum2) - min(sum1, sum2));
}

unsigned long long Solver::karmarkerkarp(vector<unsigned long long> lst)
{
    MaxHeap h = MaxHeap(lst.size());

    for (unsigned long i = 0; i < lst.size(); i++)
        h.insert(lst[i]);

    while (h.getSize() > 1)
    {
        unsigned long long max1 = h.deleteKey(0);
        unsigned long long max2 = h.deleteKey(0);
        h.insert(max1 - max2);
    }

    return h.getMax();
}

///////////////////////////////////////////////////////////////////////////////
// Standard/binary Algorithms
///////////////////////////////////////////////////////////////////////////////
vector<int> Solver::binaryRepeatedRandom()
{
    vector<int> S1 = generateBinaryList();
    unsigned long long bestResidue = residue(S1);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> S2 = generateBinaryList();
        unsigned long long novelResidue = residue(S2);
        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
        }
    }

    return S1;
}

vector<int> Solver::binaryHillClimbing()
{
    vector<int> S1 = generateBinaryList();
    unsigned long long bestResidue = residue(S1);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> S2 = generateNeighborOfBinaryList(S1);
        unsigned long long novelResidue = residue(S2);
        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
        }
    }
    return S1;
}

vector<int> Solver::binarySimulatedAnnealing()
{
    vector<int> S1 = generateBinaryList();
    vector<int> S3 = S1;
    unsigned long long bestResidue = residue(S1);
    unsigned long long S3Residue = bestResidue;

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<int> S2 = generateNeighborOfBinaryList(S1);
        unsigned long long novelResidue = residue(S2);

        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
            continue;
        }
        double randMoveProbability = exp(-1.0 * ((novelResidue - bestResidue) / (double)cooling(i)));

        if (randMoveProbability < rand.randUniform()) {
            S1 = S2;
            bestResidue = novelResidue;
        }

        if (S3Residue > bestResidue) {
            S3 = S1;
            S3Residue = bestResidue;
        }
    }

    return S3;
}

///////////////////////////////////////////////////////////////////////////////
// Prepartitioned Algorithms
///////////////////////////////////////////////////////////////////////////////
vector<unsigned long long> Solver::prepartitionedRepeatedRandom()
{
    vector<unsigned long long> S1 = generatePrepartitionedList();
    unsigned long long bestResidue = karmarkerkarp(S1);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<unsigned long long> S2 = generatePrepartitionedList();
        unsigned long long novelResidue = karmarkerkarp(S2);
        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
        }
    }
    return S1;
}

vector<unsigned long long> Solver::prepartitionedHillClimbing()
{
    vector<unsigned long long> S1 = generatePrepartitionedList();
    unsigned long long bestResidue = karmarkerkarp(S1);

    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<unsigned long long> S2 = generateNeighborOfPrepartitionedList(S1);
        unsigned long long novelResidue = karmarkerkarp(S2);
        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
        }
    }

    return S1;
}

vector<unsigned long long> Solver::prepartitionedSimulatedAnnealing()
{
    vector<unsigned long long> S1 = generatePrepartitionedList();
    vector<unsigned long long> S3 = S1;
    unsigned long long bestResidue = karmarkerkarp(S1);
    unsigned long long S3Residue = bestResidue;


    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<unsigned long long> S2 = generateNeighborOfPrepartitionedList(S1);
        unsigned long long novelResidue = karmarkerkarp(S2);

        if (bestResidue > novelResidue)
        {
            S1 = S2;
            bestResidue = novelResidue;
            continue;
        }
        double randMoveProbability = exp(-1.0 * ((novelResidue - bestResidue) / (double)cooling(i)));

        if (randMoveProbability < rand.randUniform()) {
            S1 = S2;
            bestResidue = novelResidue;
        }
        if (S3Residue > bestResidue) {
            S3 = S1;
            S3Residue = bestResidue;
        }
    }

    return S3;
}

///////////////////////////////////////////////////////////////////////////////
// Running Trials
///////////////////////////////////////////////////////////////////////////////
// Part 1 of the pset
unsigned long long Solver::solve()
{
    switch (ALG)
    {
    case 0:
        return karmarkerkarp(getList());
        break;
    case 1:
        return residue(binaryRepeatedRandom());
        break;
    case 2:
        return residue(binaryHillClimbing());
        break;
    case 3:
        return residue(binarySimulatedAnnealing());
        break;
    case 11:
        return karmarkerkarp(prepartitionedRepeatedRandom());
        break;
    case 12:
        return karmarkerkarp(prepartitionedHillClimbing());
        break;
    case 13:
        return karmarkerkarp(prepartitionedSimulatedAnnealing());
        break;
    }

    return 0;
}

// Part 2 of the pset
void Solver::runRandomTrials(int trials)
{
    cout << "Trial, KK, Standard RR, Standard HC, Standard SA, Prepartitioned RR, Prepartitioned HC, Prepartitioned SA" << endl;
    for (int i = 0; i < trials; i++)
    {
        // setList(generateRandomList());
        cout << i << ", ";
        cout << karmarkerkarp(getList()) << ", ";
        cout << residue(binaryRepeatedRandom()) << ", ";
        cout << residue(binaryHillClimbing()) << ", ";
        cout << residue(binarySimulatedAnnealing()) << ", ";
        cout << karmarkerkarp(prepartitionedRepeatedRandom()) << ", ";
        cout << karmarkerkarp(prepartitionedHillClimbing()) << ", ";
        cout << karmarkerkarp(prepartitionedSimulatedAnnealing()) << endl;
    }
}

void Solver::runRandomSimAnnealingTrials(int trials)
{
    cout << "Trial, Cooling Factor, Standard SA" << endl;
    for (int i = 0; i < trials; i++)
    {
        for (double j = 0.1; j < 5; j += 0.1)
        {
            coolingFactor = j;
            cerr << i << ", " << j << endl;
            cout << i << ", ";
            cout << j << ",";
            cout << residue(binarySimulatedAnnealing()) << endl;
            // cout << karmarkerkarp(prepartitionedSimulatedAnnealing()) << endl;
        }
    }
}

// Part 2 of the pset
void Solver::runtimes(int trials)
{
    // cout << "Trial, Standard RR, Standard HC, Standard SA, Prepartitioned RR, Prepartitioned HC, Prepartitioned SA" << endl;
    // for (int i = 0; i < trials; i++)
    // {
    //     cerr << i << endl;
    //     cout << i << ", ";

    //     chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
    //     binaryRepeatedRandom();
    //     chrono::steady_clock::time_point finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << ", ";

    //     start = chrono::high_resolution_clock::now();
    //     binaryHillClimbing();
    //     finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << ", ";

    //     start = chrono::high_resolution_clock::now();
    //     binarySimulatedAnnealing();
    //     finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << ", ";

    //     start = chrono::high_resolution_clock::now();
    //     prepartitionedRepeatedRandom();
    //     finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << ", ";

    //     start = chrono::high_resolution_clock::now();
    //     prepartitionedHillClimbing();
    //     finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << ", ";

    //     start = chrono::high_resolution_clock::now();
    //     prepartitionedSimulatedAnnealing();
    //     finish = chrono::high_resolution_clock::now();
    //     cout << (chrono::duration_cast<chrono::microseconds>(finish - start)).count() << endl;
    // }
}
