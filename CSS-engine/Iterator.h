#pragma once
#include "DL_Node.h"
template <typename T>
class Iterator
{
public:
    Iterator() noexcept :
        currentNode(nullptr) { }

    Iterator(DL_Node<T>* pNode) noexcept :
        currentNode(pNode) { }

    Iterator& operator=(DL_Node<T>* pNode)
    {
        this->currentNode = pNode;
        return *this;
    }

    Iterator& operator++()
    {
        if (currentNode)
            currentNode = currentNode->next;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator iterator = *this;
        ++* this;
        return iterator;
    }

    Iterator& operator--()
    {
        if (currentNode)
            currentNode = currentNode->previous;
        return *this;
    }

    bool operator!=(const Iterator& iterator)
    {
        return currentNode != iterator.currentNode;
    }

    T& operator*()
    {
        return currentNode->value;
    }

    DL_Node<T>* getNode() {
        return currentNode;
    }

private:
    DL_Node<T>* currentNode;
};