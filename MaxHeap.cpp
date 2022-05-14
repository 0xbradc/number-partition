#include <iostream>

#ifndef MAX_HEAP
#include "MaxHeap.h"
#define MAX_HEAP
#endif

using namespace std;

MaxHeap::MaxHeap(int cap)
{
	harr = vector<unsigned long long>(cap);
	size = 0;
	capacity = cap;
}

unsigned long long MaxHeap::getMax()
{
	if (size == 0)
		throw "getMax: Heap is empty";
	return harr[0];
}

int MaxHeap::getSize() { return size; }

int MaxHeap::getCapacity() { return capacity; }

int MaxHeap::parent(int i)
{
	if (i == 0)
		throw "parent: Index is 0";
	return (i - 1) / 2;
}

int MaxHeap::left(int i) { return 2 * i + 1; }

int MaxHeap::right(int i) { return 2 * i + 2; }

void MaxHeap::insert(unsigned long long i)
{
	if (size == capacity)
		throw "insert: Heap is full";
	harr[size] = i;
	size++;
	int j = size - 1;
	while (j > 0 && harr[parent(j)] < harr[j])
	{
		swap(j, parent(j));
		j = parent(j);
	}
}

unsigned long long MaxHeap::deleteKey(int i)
{
	if (i < 0 || i >= size)
		throw "deleteKey: Index is out of range";

	unsigned long long max = harr[i];
	swap(i, size - 1);
	size--;
	heapify(i);
	return max;
}

void MaxHeap::swap(int i, int j)
{
	if (i < 0 || i >= size || j < 0 || j >= size)
		throw "swap: Index out of bound";
	unsigned long long temp = harr[i];
	harr[i] = harr[j];
	harr[j] = temp;
}

void MaxHeap::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l < size && harr[l] > harr[i])
		largest = l;
	if (r < size && harr[r] > harr[largest])
		largest = r;

	// largest not at the root
	if (largest != i)
	{
		swap(i, largest);
		// recursively heapify the affected sub-tree
		heapify(largest);
	}
}

void MaxHeap::print()
{
	for (int i = 0; i < size; i++)
		cout << harr[i] << " ";
	cout << endl;
}