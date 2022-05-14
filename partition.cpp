#include <iostream>
#include <vector>
#include "fileReader.h"
#include "Solver.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "Usage: ./partition <flag> <algorithm> <inputfile>" << endl;
        exit(1);
    }
    const int FLAG = atoi(argv[1]);
    const int ALGORITHM = atoi(argv[2]);
    const vector<unsigned long long> NUM_LIST = fileReader(argv[3]);

    Solver s = Solver(ALGORITHM, NUM_LIST);
    cout << s.solve();
    cout.flush();
    return 0;
}
