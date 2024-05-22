#pragma once
#include "DL_Node.h"
#include "Iterator.h"
using namespace std;

template <typename T> class DL_List {
private:
	int size;
	DL_Node<T>* head;
	DL_Node<T>* tail;
public:

	DL_List() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	~DL_List() {
		while (head != nullptr) {
			DL_Node<T>* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void push_front(T object) {
		DL_Node<T>* tmp;
		tmp = new DL_Node<T>;
		tmp->value = object;
		tmp->next = head;
		tmp->previous = nullptr;
		if (head != nullptr) {
			head->previous = tmp;
		}
		head = tmp;
		if (tail == nullptr) tail = tmp;
		size++;
	}
	void push_back(T object) {
		DL_Node<T>* tmp;
		tmp = new DL_Node<T>;
		tmp->value = object;
		tmp->previous = tail;
		tmp->next = nullptr;
		if (tail != nullptr) {
			tail->next = tmp;
		}
		tail = tmp;
		if (head == nullptr) head = tmp;
		size++;
	}
	int getSize() {
		return size;
	}
	T* getElement(size_t index) {
		if (index > size) return nullptr;
		DL_Node<T>* pointer = nullptr;
		if (index > size / 2) {
			pointer = tail;
			for (int i = size; i > index; i--) {
				pointer = pointer->previous;
			}
		}
		else {
			pointer = head;
			for (int i = 1; i < index; i++) {
				pointer = pointer->next;
			}
		}
		return &(pointer->value);
	}

	void removeNode(DL_Node<T>* pointer) {
		if (head == pointer) {
			head = pointer->next;
		}
		if (tail == pointer) {
			tail = pointer->previous;
		}
		if (pointer->previous != nullptr) {
			pointer->previous->next = pointer->next;
		}
		if (pointer->next != nullptr) {
			pointer->next->previous = pointer->previous;
		}
		delete pointer;
		size--;
	}

	 DL_Node<T>* begin() {
		return head;
	}

	Iterator<T> end() {
		return Iterator<T>(nullptr);
	}
};