#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <utility>
#include <stdexcept>

// Purpose: A generic dynamic array template class simulating std::vector.
// Responsibilities: Handles dynamic contiguous memory allocation, element insertion, removal, and copying.
// Data Structure Used: Contiguous Dynamic Array
// Time Complexity: Access: O(1), push_back: Amortized O(1), pop_back: O(1), Insert/Delete: O(N) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>, <stdexcept>
template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t length;

    // Purpose: Resize internal buffer to new capacity | Parameters: newCapacity (size_t) | Return Value: None | Complexity: O(N)
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    DynamicArray() : data(nullptr), capacity(0), length(0) {}

    // Purpose: Parameterized Constructor | Parameters: initialCapacity (size_t) | Return Value: None | Complexity: O(N)
    explicit DynamicArray(size_t initialCapacity)
        : data(new T[initialCapacity]), capacity(initialCapacity), length(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~DynamicArray() {
        delete[] data;
    }

    // Purpose: Copy Constructor | Parameters: other (const DynamicArray&) | Return Value: None | Complexity: O(N)
    DynamicArray(const DynamicArray& other)
        : data(nullptr), capacity(other.capacity), length(other.length) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const DynamicArray&) | Return Value: DynamicArray& | Complexity: O(N)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            T* newData = nullptr;
            if (other.capacity > 0) {
                newData = new T[other.capacity];
                for (size_t i = 0; i < other.length; ++i) {
                    newData[i] = other.data[i];
                }
            }
            delete[] data;
            data = newData;
            capacity = other.capacity;
            length = other.length;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (DynamicArray&&) | Return Value: None | Complexity: O(1)
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), capacity(other.capacity), length(other.length) {
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (DynamicArray&&) | Return Value: DynamicArray& | Complexity: O(1)
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            length = other.length;
            other.data = nullptr;
            other.capacity = 0;
            other.length = 0;
        }
        return *this;
    }

    // Purpose: Append element to array | Parameters: value (const T&) | Return Value: None | Complexity: Amortized O(1)
    void push_back(const T& value) {
        if (length == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[length++] = value;
    }

    // Purpose: Remove last element from array | Parameters: None | Return Value: None | Complexity: O(1)
    void pop_back() {
        if (length > 0) {
            length--;
        }
    }

    // Purpose: Access element by index | Parameters: index (size_t) | Return Value: T& | Complexity: O(1)
    T& operator[](size_t index) {
        return data[index];
    }

    // Purpose: Access element by index (const) | Parameters: index (size_t) | Return Value: const T& | Complexity: O(1)
    const T& operator[](size_t index) const {
        return data[index];
    }

    // Purpose: Access element by index with bounds checking | Parameters: index (size_t) | Return Value: T& | Complexity: O(1)
    T& at(size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of bounds in DynamicArray::at");
        }
        return data[index];
    }

    // Purpose: Access element by index with bounds checking (const) | Parameters: index (size_t) | Return Value: const T& | Complexity: O(1)
    const T& at(size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of bounds in DynamicArray::at");
        }
        return data[index];
    }

    // Purpose: Get number of elements | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return length;
    }

    // Purpose: Get current allocated capacity | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getCapacity() const {
        return capacity;
    }

    // Purpose: Check if array is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return length == 0;
    }

    // Purpose: Clear all elements | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        length = 0;
    }
};

#endif // DYNAMIC_ARRAY_H
