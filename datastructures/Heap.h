#ifndef HEAP_H
#define HEAP_H

#include <cstddef>
#include <utility>
#include <stdexcept>
#include "DynamicArray.h"

template <typename T>
struct Less {
    // Purpose: Default comparator structure | Parameters: lhs (const T&), rhs (const T&) | Return Value: bool | Complexity: O(1)
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

// Purpose: A generic template Binary Heap class (Max Heap / Min Heap depending on Compare).
// Responsibilities: Maintains heap invariant, supports element insertion, extraction of top element, and peeking.
// Data Structure Used: Array-based Binary Heap using DynamicArray
// Time Complexity: Insert: O(log N), Extract: O(log N), Peek: O(1) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>, <stdexcept>, "DynamicArray.h"
template <typename T, typename Compare = Less<T>>
class Heap {
private:
    DynamicArray<T> data;
    Compare comp;

    // Purpose: Restore heap property upwards | Parameters: index (size_t) | Return Value: None | Complexity: O(log N)
    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t p = parent(index);
            if (comp(data[p], data[index])) {
                std::swap(data[index], data[p]);
                index = p;
            } else {
                break;
            }
        }
    }

    // Purpose: Restore heap property downwards | Parameters: index (size_t) | Return Value: None | Complexity: O(log N)
    void heapifyDown(size_t index) {
        size_t size = data.getSize();
        while (leftChild(index) < size) {
            size_t best = index;
            size_t left = leftChild(index);
            size_t right = rightChild(index);

            if (comp(data[best], data[left])) {
                best = left;
            }
            if (right < size && comp(data[best], data[right])) {
                best = right;
            }

            if (best != index) {
                std::swap(data[index], data[best]);
                index = best;
            } else {
                break;
            }
        }
    }

    // Purpose: Get parent index | Parameters: child (size_t) | Return Value: size_t | Complexity: O(1)
    size_t parent(size_t child) const {
        if (child == 0) return 0;
        return (child - 1) / 2;
    }

    // Purpose: Get left child index | Parameters: parent (size_t) | Return Value: size_t | Complexity: O(1)
    size_t leftChild(size_t parent) const {
        return 2 * parent + 1;
    }

    // Purpose: Get right child index | Parameters: parent (size_t) | Return Value: size_t | Complexity: O(1)
    size_t rightChild(size_t parent) const {
        return 2 * parent + 2;
    }

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Heap() : data(), comp() {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Heap() = default;

    // Purpose: Copy Constructor | Parameters: other (const Heap&) | Return Value: None | Complexity: O(N)
    Heap(const Heap& other) : data(other.data), comp(other.comp) {}

    // Purpose: Copy Assignment Operator | Parameters: other (const Heap&) | Return Value: Heap& | Complexity: O(N)
    Heap& operator=(const Heap& other) {
        if (this != &other) {
            data = other.data;
            comp = other.comp;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (Heap&&) | Return Value: None | Complexity: O(1)
    Heap(Heap&& other) noexcept : data(std::move(other.data)), comp(std::move(other.comp)) {}

    // Purpose: Move Assignment Operator | Parameters: other (Heap&&) | Return Value: Heap& | Complexity: O(1)
    Heap& operator=(Heap&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            comp = std::move(other.comp);
        }
        return *this;
    }

    // Purpose: Insert value into heap | Parameters: value (const T&) | Return Value: None | Complexity: O(log N)
    void insert(const T& value) {
        data.push_back(value);
        heapifyUp(data.getSize() - 1);
    }

    // Purpose: Extract the top element from heap | Parameters: outValue (T&) | Return Value: bool | Complexity: O(log N)
    bool extractTop(T& outValue) {
        if (isEmpty()) {
            return false;
        }
        outValue = data[0];
        size_t size = data.getSize();
        data[0] = data[size - 1];
        data.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return true;
    }

    // Purpose: Peek the top element of heap | Parameters: None | Return Value: T& | Complexity: O(1)
    T& peek() {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        return data[0];
    }

    // Purpose: Peek the top element of heap (const) | Parameters: None | Return Value: const T& | Complexity: O(1)
    const T& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        return data[0];
    }

    // Purpose: Check if heap is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return data.isEmpty();
    }

    // Purpose: Get size of the heap | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return data.getSize();
    }

    // Purpose: Clear all elements | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        data.clear();
    }
};

#endif // HEAP_H
