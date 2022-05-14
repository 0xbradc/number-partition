#include <iostream>
#include <vector>
#include "Solver.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: ./test <flag> <algorithm>" << endl;
        exit(1);
    }
    const int FLAG = atoi(argv[1]);
    const int ALGORITHM = atoi(argv[2]);

    Solver solver = Solver(ALGORITHM);
    // solver.printList();

    // Part 2 of the assignment to run 50 trials
    solver.runtimes(100);

    return 0;
}
