CC = g++

partition: partition.cpp
	$(CC) -std=c++17 -O3 -Wall -Wextra partition.cpp fileReader.cpp MaxHeap.cpp Solver.cpp Random.cpp -o partition -lm

test: test.cpp
	$(CC) -std=c++17 -O3 -Wall -Wextra test.cpp fileReader.cpp MaxHeap.cpp Solver.cpp Random.cpp -o test -lm

