#pragma once
#include "Block_Node.h"
#include "Block_Iterator.h"
using namespace std;

template <typename T> class Block_List {
private:
	int size;
	Block_Node<T>* head;
	Block_Node<T>* tail;
public:
	Block_List() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	~Block_List() {
		while (head != nullptr) {
			Block_Node<T>* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void push_back(T object) {
		if (tail == nullptr || tail->isOccupied[SIZE-1]) {
			Block_Node<T>* tmp = new Block_Node<T>;
			tmp->value[0] = object;
			tmp->isOccupied[0] = 1;
			tmp->nrOccupied++;
			tmp->next = nullptr;
			tmp->previous = tail;
			if (tail != nullptr) {
				tail->next = tmp;
			}
			tail = tmp;
			if (head == nullptr) head = tmp;
		}
		else {
			int i = SIZE - 2;
			for (; i > 0; i--) {
				if (tail->isOccupied[i]) {
					break;
				}
			}
			i++;
			tail->value[i] = object;
			tail->isOccupied[i] = 1;
			tail->nrOccupied++;
		}
		size++;
	}
	int getSize() {
		return size;
	}
	T* getElement(int index) {
		if (index > size) return nullptr;
		Block_Node<T>* pointer = nullptr;
		if (index > size / 2) {
			int iterator = size;
			pointer = tail;
			while (index <= iterator - (pointer->nrOccupied)) {
				iterator -= pointer->nrOccupied;
				pointer = pointer->previous;
			}
			int prettyName = SIZE - 1;
			while (iterator >= index) {
				if (pointer->isOccupied[prettyName]) {
					iterator--;
				}
				prettyName--;
			}
			return &(pointer->value[prettyName+1]);
		}
		else {
			int iterator = 1;
			pointer = head;
			while (index >= iterator + (pointer->nrOccupied)) {
				iterator += pointer->nrOccupied;
				pointer = pointer->next;
			}
			int prettyName = 0;
			while (iterator <= index) {
				if (pointer->isOccupied[prettyName]) {
					iterator++;
				}
				prettyName++;
			}
			return &(pointer->value[prettyName - 1]);
		}
	}

	bool removeAt(int index) {
		if (index > size) return 0;
		Block_Node<T>* pointer = nullptr;
		if (index > size / 2) {
			int iterator = size;
			pointer = tail;
			while (index <= iterator - pointer->nrOccupied) {
				iterator -= pointer->nrOccupied;
				pointer = pointer->previous;
			}
			int indeksSekcji = SIZE - 1;
			while (iterator >= index) {
				if (pointer->isOccupied[indeksSekcji]) {
					iterator--;
				}
				indeksSekcji--;
			}
			indeksSekcji++;
			pointer->isOccupied[indeksSekcji] = 0;
			pointer->nrOccupied--;
			delete pointer->value[indeksSekcji];
			if (pointer->nrOccupied == 0) {
				removeNode(pointer);
			}
		}
		else {
			int iterator = 1;
			pointer = head;
			while (index >= iterator + pointer->nrOccupied) {
				iterator += pointer->nrOccupied;
				pointer = pointer->next;
			}
			int indeksSekcji = 0;
			while (iterator <= index) {
				if (pointer->isOccupied[indeksSekcji]) {
					iterator++;
				}
				indeksSekcji++;
			}
			indeksSekcji--;
			pointer->isOccupied[indeksSekcji] = 0;
			pointer->nrOccupied--;
			delete pointer->value[indeksSekcji];
			pointer->value[indeksSekcji] = nullptr;
			if (pointer->nrOccupied == 0) {
				removeNode(pointer);
			}
		}
		size--;
		return 1;
	}

	void removeNode(Block_Node<T>* pointer) {
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
	}

	Block_Node<T>* begin() {
		return head;
	}

	Block_Iterator<T> end() {
		return Block_Iterator<T>();
	}

};