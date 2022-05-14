#include<vector>

using namespace std;

class MaxHeap
{
  private:
    vector<unsigned long long> harr;
    int size;
    int capacity;

  public:
    MaxHeap(int cap);

    unsigned long long getMax();
    int getSize();
    int getCapacity();
    int parent(int i);
    int left(int i);
    int right(int i);


    void insert(unsigned long long i);
    unsigned long long deleteKey(int k);
    void swap(int i, int j);
    void heapify(int i);

    void print();
};