#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <utility>
#include <stdexcept>

// Purpose: A generic template Stack class (LIFO - Last In First Out).
// Responsibilities: Support standard stack push, pop, top, and empty queries.
// Data Structure Used: Node-based singly linked stack representation.
// Time Complexity: Push/Pop/Top: O(1) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>, <stdexcept>
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* topNode;
    size_t size;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Stack() : topNode(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~Stack() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const Stack&) | Return Value: None | Complexity: O(N)
    Stack(const Stack& other) : topNode(nullptr), size(0) {
        if (other.topNode == nullptr) {
            return;
        }
        Node* current = other.topNode;
        Node* tail = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->data);
            if (topNode == nullptr) {
                topNode = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            current = current->next;
            size++;
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const Stack&) | Return Value: Stack& | Complexity: O(N)
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            if (other.topNode != nullptr) {
                Node* current = other.topNode;
                Node* tail = nullptr;
                while (current != nullptr) {
                    Node* newNode = new Node(current->data);
                    if (topNode == nullptr) {
                        topNode = newNode;
                    } else {
                        tail->next = newNode;
                    }
                    tail = newNode;
                    current = current->next;
                    size++;
                }
            }
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (Stack&&) | Return Value: None | Complexity: O(1)
    Stack(Stack&& other) noexcept : topNode(other.topNode), size(other.size) {
        other.topNode = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (Stack&&) | Return Value: Stack& | Complexity: O(1)
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            clear();
            topNode = other.topNode;
            size = other.size;
            other.topNode = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Push an element onto the stack | Parameters: value (const T&) | Return Value: None | Complexity: O(1)
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    // Purpose: Remove the top element from stack | Parameters: None | Return Value: bool | Complexity: O(1)
    bool pop() {
        if (topNode == nullptr) {
            return false;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        size--;
        return true;
    }

    // Purpose: Return the top element of the stack | Parameters: None | Return Value: T& | Complexity: O(1)
    T& top() {
        if (topNode == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return topNode->data;
    }

    // Purpose: Return the top element of the stack (const) | Parameters: None | Return Value: const T& | Complexity: O(1)
    const T& top() const {
        if (topNode == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return topNode->data;
    }

    // Purpose: Check if stack is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Get the number of elements in stack | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Clear all elements from stack | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        while (pop()) {}
    }
};

#endif // STACK_H
