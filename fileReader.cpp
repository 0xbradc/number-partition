#include "fileReader.h"

using namespace std;

vector<unsigned long long> fileReader(char *file)
{
    vector<unsigned long long> num_list;

    try
    {
        // Read each line of file into each element of a vector
        ifstream myfile(file);
        string line;
        while (getline(myfile, line))
        {
            stringstream ss(line);
            unsigned long long num;
            while (ss >> num)
                num_list.push_back(num);
        }
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }

    return num_list;
}