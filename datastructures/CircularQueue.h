#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <cstddef>
#include <utility>
#include <stdexcept>

// Purpose: A generic template Circular Queue class.
// Responsibilities: Manages a circular buffer of items, preventing index overrun and reusing memory efficiently.
// Data Structure Used: Circular Array Buffer
// Time Complexity: Enqueue/Dequeue/Front: O(1) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>, <stdexcept>
template <typename T>
class CircularQueue {
private:
    T* data;
    size_t capacity;
    size_t headIndex;
    size_t tailIndex;
    size_t length;

public:
    // Purpose: Parameterized Constructor | Parameters: queueCapacity (size_t) | Return Value: None | Complexity: O(N)
    explicit CircularQueue(size_t queueCapacity)
        : data(new T[queueCapacity]), capacity(queueCapacity), headIndex(0), tailIndex(0), length(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~CircularQueue() {
        delete[] data;
    }

    // Purpose: Copy Constructor | Parameters: other (const CircularQueue&) | Return Value: None | Complexity: O(N)
    CircularQueue(const CircularQueue& other)
        : data(new T[other.capacity]), capacity(other.capacity), headIndex(other.headIndex), tailIndex(other.tailIndex), length(other.length) {
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const CircularQueue&) | Return Value: CircularQueue& | Complexity: O(N)
    CircularQueue& operator=(const CircularQueue& other) {
        if (this != &other) {
            T* newData = new T[other.capacity];
            for (size_t i = 0; i < other.capacity; ++i) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            capacity = other.capacity;
            headIndex = other.headIndex;
            tailIndex = other.tailIndex;
            length = other.length;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (CircularQueue&&) | Return Value: None | Complexity: O(1)
    CircularQueue(CircularQueue&& other) noexcept
        : data(other.data), capacity(other.capacity), headIndex(other.headIndex), tailIndex(other.tailIndex), length(other.length) {
        other.data = nullptr;
        other.capacity = 0;
        other.headIndex = 0;
        other.tailIndex = 0;
        other.length = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (CircularQueue&&) | Return Value: CircularQueue& | Complexity: O(1)
    CircularQueue& operator=(CircularQueue&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            headIndex = other.headIndex;
            tailIndex = other.tailIndex;
            length = other.length;
            other.data = nullptr;
            other.capacity = 0;
            other.headIndex = 0;
            other.tailIndex = 0;
            other.length = 0;
        }
        return *this;
    }

    // Purpose: Enqueue an element into circular queue | Parameters: value (const T&) | Return Value: bool | Complexity: O(1)
    bool enqueue(const T& value) {
        if (isFull()) {
            return false;
        }
        data[tailIndex] = value;
        tailIndex = (tailIndex + 1) % capacity;
        length++;
        return true;
    }

    // Purpose: Dequeue an element from circular queue | Parameters: None | Return Value: bool | Complexity: O(1)
    bool dequeue() {
        if (isEmpty()) {
            return false;
        }
        headIndex = (headIndex + 1) % capacity;
        length--;
        return true;
    }

    // Purpose: Get reference to front element | Parameters: None | Return Value: T& | Complexity: O(1)
    T& front() {
        if (isEmpty()) {
            throw std::out_of_range("CircularQueue is empty");
        }
        return data[headIndex];
    }

    // Purpose: Get reference to front element (const) | Parameters: None | Return Value: const T& | Complexity: O(1)
    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("CircularQueue is empty");
        }
        return data[headIndex];
    }

    // Purpose: Check if queue is full | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isFull() const {
        return length == capacity;
    }

    // Purpose: Check if queue is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return length == 0;
    }

    // Purpose: Get the current size | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return length;
    }

    // Purpose: Get maximum capacity | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getCapacity() const {
        return capacity;
    }

    // Purpose: Clear all queue elements | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        headIndex = 0;
        tailIndex = 0;
        length = 0;
    }
};

#endif // CIRCULAR_QUEUE_H
