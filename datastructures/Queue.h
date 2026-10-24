#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <utility>
#include <stdexcept>

// Purpose: A generic template Queue class (FIFO - First In First Out).
// Responsibilities: Support standard queue operations including enqueue, dequeue, front, and size checking.
// Data Structure Used: Node-based singly linked queue representation.
// Time Complexity: Enqueue/Dequeue/Front: O(1) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>, <stdexcept>
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    size_t size;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Queue() : frontNode(nullptr), rearNode(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~Queue() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const Queue&) | Return Value: None | Complexity: O(N)
    Queue(const Queue& other) : frontNode(nullptr), rearNode(nullptr), size(0) {
        Node* current = other.frontNode;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const Queue&) | Return Value: Queue& | Complexity: O(N)
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            Node* current = other.frontNode;
            while (current != nullptr) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (Queue&&) | Return Value: None | Complexity: O(1)
    Queue(Queue&& other) noexcept : frontNode(other.frontNode), rearNode(other.rearNode), size(other.size) {
        other.frontNode = nullptr;
        other.rearNode = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (Queue&&) | Return Value: Queue& | Complexity: O(1)
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();
            frontNode = other.frontNode;
            rearNode = other.rearNode;
            size = other.size;
            other.frontNode = nullptr;
            other.rearNode = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Add an element to the rear of the queue | Parameters: value (const T&) | Return Value: None | Complexity: O(1)
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        size++;
    }

    // Purpose: Remove the front element from the queue | Parameters: None | Return Value: bool | Complexity: O(1)
    bool dequeue() {
        if (frontNode == nullptr) {
            return false;
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    // Purpose: Get reference to front element | Parameters: None | Return Value: T& | Complexity: O(1)
    T& front() {
        if (frontNode == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return frontNode->data;
    }

    // Purpose: Get reference to front element (const) | Parameters: None | Return Value: const T& | Complexity: O(1)
    const T& front() const {
        if (frontNode == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return frontNode->data;
    }

    // Purpose: Check if queue is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Get current number of elements | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Clear all elements from queue | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        while (dequeue()) {}
    }
};

#endif // QUEUE_H
