#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
class StackNode {
public:
    T data;
    StackNode* next;

    StackNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    StackNode<T>* topNode;
    int size;

public:
    Stack() : topNode(nullptr), size(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Stack Underflow! Cannot pop.\n";
            return;
        }
        StackNode<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        size--;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int getSize() const {
        return size;
    }
    
    // Allows traversal without modifying stack
    StackNode<T>* getTopNode() const {
        return topNode;
    }
};

#endif // STACK_H
