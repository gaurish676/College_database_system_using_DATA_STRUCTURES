#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <utility>

// Purpose: A generic singly linked list template class.
// Responsibilities: Manage sequential nodes, pointer linkages, traversal, insertion, and deletion.
// Data Structure Used: Singly Linked List
// Time Complexity: Insertion/Deletion at head: O(1), Insertion/Deletion at tail/middle: O(N), Search: O(N) | Space Complexity: O(N)
// Dependencies: <cstddef>, <utility>
template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;

        Node(const T& val) : data(val), next(nullptr) {}
    };

private:
    Node* head;
    size_t size;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    LinkedList() : head(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~LinkedList() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const LinkedList&) | Return Value: None | Complexity: O(N)
    LinkedList(const LinkedList& other) : head(nullptr), size(0) {
        Node* current = other.head;
        Node* tail = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->data);
            if (head == nullptr) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            current = current->next;
            size++;
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const LinkedList&) | Return Value: LinkedList& | Complexity: O(N)
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            Node* tail = nullptr;
            while (current != nullptr) {
                Node* newNode = new Node(current->data);
                if (head == nullptr) {
                    head = newNode;
                } else {
                    tail->next = newNode;
                }
                tail = newNode;
                current = current->next;
                size++;
            }
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (LinkedList&&) | Return Value: None | Complexity: O(1)
    LinkedList(LinkedList&& other) noexcept : head(other.head), size(other.size) {
        other.head = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (LinkedList&&) | Return Value: LinkedList& | Complexity: O(1)
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Insert element at the beginning | Parameters: value (const T&) | Return Value: None | Complexity: O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Purpose: Insert element at the end | Parameters: value (const T&) | Return Value: None | Complexity: O(N)
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
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
        delete temp;
        size--;
        return true;
    }

    // Purpose: Find and remove a specific value | Parameters: value (const T&) | Return Value: bool | Complexity: O(N)
    bool remove(const T& value) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp != nullptr) {
            if (temp->data == value) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    // Purpose: Get pointer to the head node | Parameters: None | Return Value: Node* | Complexity: O(1)
    Node* getHead() {
        return head;
    }

    // Purpose: Get pointer to the head node (const) | Parameters: None | Return Value: const Node* | Complexity: O(1)
    const Node* getHead() const {
        return head;
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
};

#endif // LINKED_LIST_H
