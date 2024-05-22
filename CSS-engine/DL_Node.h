#pragma once
using namespace std;

template <typename T> class DL_Node {

public:
	T value;
	DL_Node<T>* next;
	DL_Node<T>* previous;
	DL_Node() {
		next = nullptr;
		previous = nullptr;
	}
	DL_Node(T newValue) {
		value = newValue;
		next = nullptr;
		previous = nullptr;
	}
};