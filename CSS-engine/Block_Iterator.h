#pragma once
#include "Block_Node.h"
template <typename T>
class Block_Iterator
{
public:
    Block_Iterator() noexcept :
        currentNode(nullptr), index(0) { }

    Block_Iterator(Block_Node<T>* pNode) noexcept :
        currentNode(pNode), index(0) {
        if (currentNode != nullptr) {
            while (!currentNode->isOccupied[index]) {
                index++;
            }
        }
    }

    Block_Iterator(Block_Node<T>* pNode, int pIndex) noexcept :
        currentNode(pNode), index(pIndex) { }

    Block_Iterator& operator=(Block_Node<T>* pNode)
    {
        this->currentNode = pNode;
        this->index = 0;
        if (currentNode != nullptr) {
            while (!currentNode->isOccupied[index]) {
                index++;
            }
        }
        return *this;
    }

    // Prefix ++ overload
    Block_Iterator& operator++()
    {
        if (currentNode) {
            index++;
            while (index < SIZE && !(currentNode->isOccupied[index]))
            {
                index++;
            }
            if (index >= SIZE) {
                currentNode = currentNode->next;
                index = 0;
                while (currentNode != nullptr && !(currentNode->isOccupied[index]))
                {
                    index++;
                }
            }
        }
        return *this;
    }

    /*Iterator& operator--()
    {
        if (m_pCurrentNode)
            m_pCurrentNode = m_pCurrentNode->previous;
        return *this;
    }*/

    // Postfix ++ overload
    Block_Iterator operator++(int)
    {
        Block_Iterator iterator = *this;
        ++* this;
        return iterator;
    }

    bool operator!=(const Block_Iterator& iterator)
    {
            if (currentNode == iterator.currentNode) {
                return (index != iterator.index);
            }
            else return true;
    }

    T& operator*()
    {
        return currentNode->value[index];
    }

    Block_Node<T>* getNode() {
        return currentNode;
    }

private:
   Block_Node<T>* currentNode;
   int index;
};