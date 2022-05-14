#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Random.h"

#ifndef MAX_HEAP
#include "MaxHeap.h"
#define MAX_HEAP
#endif

using namespace std;

class Solver
{
private:
    int ALG;
    int LIST_SIZE;
    int MAX_ITER;
    vector<unsigned long long> list;
    Random rand;
    double coolingFactor;

public:
    ///////////////////////////////////////////////////////////////////////////////
    // Constructors
    ///////////////////////////////////////////////////////////////////////////////
    Solver();
    Solver(int alg, double coolFactor = 0.8);
    Solver(int alg, vector<unsigned long long> lst, double coolFactor = 0.8);


    ///////////////////////////////////////////////////////////////////////////////
    // Getters, Setters, Printers
    ///////////////////////////////////////////////////////////////////////////////
    int getAlgorithm();
    vector<unsigned long long> getList();
    void setList(vector<unsigned long long> lst);
    void printList();


    ///////////////////////////////////////////////////////////////////////////////
    // Random Generators
    ///////////////////////////////////////////////////////////////////////////////
    vector<unsigned long long> generateRandomList();
    vector<int> generateBinaryList();
    vector<unsigned long long> generatePrepartitionedList();
    vector<int> generateNeighborOfBinaryList(vector<int> lst);
    vector<unsigned long long> generateNeighborOfPrepartitionedList(vector<unsigned long long> original);


    ///////////////////////////////////////////////////////////////////////////////
    // Operations
    ///////////////////////////////////////////////////////////////////////////////
    int cooling(int iter);
    unsigned long long residue(vector<int> lst);
    unsigned long long karmarkerkarp(vector<unsigned long long> lst);
    vector<int> binaryRepeatedRandom();
    vector<int> binaryHillClimbing();
    vector<int> binarySimulatedAnnealing();
    vector<unsigned long long> prepartitionedRepeatedRandom();
    vector<unsigned long long> prepartitionedHillClimbing();
    vector<unsigned long long> prepartitionedSimulatedAnnealing();


    ///////////////////////////////////////////////////////////////////////////////
    // Running Trials
    ///////////////////////////////////////////////////////////////////////////////
    unsigned long long solve();
    void runRandomTrials(int trials);
    void runRandomSimAnnealingTrials(int trials);
    void runtimes(int trials);
};