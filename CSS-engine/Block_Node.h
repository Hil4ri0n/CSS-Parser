#pragma once
#define SIZE 8
using namespace std;

template <typename T> class Block_Node {

public:
	int nrOccupied;
	T value[SIZE];
	bool isOccupied[SIZE];
	Block_Node<T>* next;
	Block_Node<T>* previous;
	Block_Node() {
		nrOccupied = 0;
		for (int i = 0; i < SIZE; i++) {
			isOccupied[i] = false;
		}
		next = nullptr;
		previous = nullptr;
	}
};