#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <utility>

// Purpose: A generic doubly linked list template class.
// Responsibilities: Maintain forward/backward pointers, insert and remove nodes at either end or in the middle.
// Data Structure Used: Doubly Linked List
// Time Complexity: Insertion/Deletion at head/tail: O(1), Insertion/Deletion in middle: O(N), Search: O(N) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>
template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }
        Node* getNode() { return current; }
        Iterator& operator++() { if (current) current = current->next; return *this; }
        Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }
        Iterator& operator--() { if (current) current = current->prev; return *this; }
        Iterator operator--(int) { Iterator temp = *this; --(*this); return temp; }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

private:
    Node* head;
    Node* tail;
    size_t size;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~DoublyLinkedList() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const DoublyLinkedList&) | Return Value: None | Complexity: O(N)
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const DoublyLinkedList&) | Return Value: DoublyLinkedList& | Complexity: O(N)
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (DoublyLinkedList&&) | Return Value: None | Complexity: O(1)
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (DoublyLinkedList&&) | Return Value: DoublyLinkedList& | Complexity: O(1)
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Insert element at the beginning | Parameters: value (const T&) | Return Value: None | Complexity: O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Purpose: Insert element at the end | Parameters: value (const T&) | Return Value: None | Complexity: O(1)
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Purpose: Remove element from the beginning | Parameters: None | Return Value: bool | Complexity: O(1)
    bool pop_front() {
        if (head == nullptr) {
            return false;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    // Purpose: Remove element from the end | Parameters: None | Return Value: bool | Complexity: O(1)
    bool pop_back() {
        if (tail == nullptr) {
            return false;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    // Purpose: Remove a node matching a specific value | Parameters: value (const T&) | Return Value: bool | Complexity: O(N)
    bool remove(const T& value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return removeNode(temp);
            }
            temp = temp->next;
        }
        return false;
    }

    // Purpose: Remove a specific node directly from list | Parameters: node (Node*) | Return Value: bool | Complexity: O(1)
    bool removeNode(Node* node) {
        if (node == nullptr) {
            return false;
        }
        if (node == head) {
            return pop_front();
        }
        if (node == tail) {
            return pop_back();
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
        return true;
    }

    // Purpose: Get pointer to the head node | Parameters: None | Return Value: Node* | Complexity: O(1)
    Node* getHead() {
        return head;
    }

    // Purpose: Get pointer to the head node (const) | Parameters: None | Return Value: const Node* | Complexity: O(1)
    const Node* getHead() const {
        return head;
    }

    // Purpose: Get pointer to the tail node | Parameters: None | Return Value: Node* | Complexity: O(1)
    Node* getTail() {
        return tail;
    }

    // Purpose: Get pointer to the tail node (const) | Parameters: None | Return Value: const Node* | Complexity: O(1)
    const Node* getTail() const {
        return tail;
    }

    // Purpose: Get size of the list | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Check if list is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Clear all nodes from list | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        while (pop_front()) {}
    }

    // Purpose: Get Iterator for beginning of list | Parameters: None | Return Value: Iterator | Complexity: O(1)
    Iterator begin() {
        return Iterator(head);
    }

    // Purpose: Get Iterator for end of list | Parameters: None | Return Value: Iterator | Complexity: O(1)
    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif // DOUBLY_LINKED_LIST_H
