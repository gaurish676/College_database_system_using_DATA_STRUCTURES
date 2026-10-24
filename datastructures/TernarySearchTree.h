#ifndef TERNARY_SEARCH_TREE_H
#define TERNARY_SEARCH_TREE_H

#include <cstddef>
#include <string>
#include <utility>
#include "DynamicArray.h"

// Purpose: A Ternary Search Tree (TST) for fast string prefix searching and auto-completion indexes.
// Responsibilities: Inserts, removes, searches string keys, and retrieves prefix match results.
// Data Structure Used: Ternary Search Tree (TST)
// Time Complexity: Search/Insert/Delete: O(L) where L is string length | Space Complexity: O(N * L)
// Dependencies: <cstddef>, <string>, <utility>, "DynamicArray.h"
template <typename V>
class TernarySearchTree {
public:
    struct Node {
        char splitChar;
        Node* left;
        Node* mid;
        Node* right;
        bool isEnd;
        V value;

        Node(char ch)
            : splitChar(ch), left(nullptr), mid(nullptr), right(nullptr), isEnd(false), value(V()) {}
    };

private:
    Node* root;
    size_t size;

    // Purpose: Recursive insertion helper | Parameters: node (Node*), key (const std::string&), index (size_t), value (const V&), inserted (bool&) | Return Value: Node* | Complexity: O(L)
    Node* insertHelper(Node* node, const std::string& key, size_t index, const V& value, bool& inserted) {
        char ch = key[index];
        if (node == nullptr) {
            node = new Node(ch);
        }

        if (ch < node->splitChar) {
            node->left = insertHelper(node->left, key, index, value, inserted);
        } else if (ch > node->splitChar) {
            node->right = insertHelper(node->right, key, index, value, inserted);
        } else {
            if (index + 1 < key.length()) {
                node->mid = insertHelper(node->mid, key, index + 1, value, inserted);
            } else {
                if (!node->isEnd) {
                    inserted = true;
                }
                node->isEnd = true;
                node->value = value;
            }
        }
        return node;
    }

    // Purpose: Recursive search helper | Parameters: node (Node*), key (const std::string&), index (size_t), outValue (V&) | Return Value: bool | Complexity: O(L)
    bool searchHelper(Node* node, const std::string& key, size_t index, V& outValue) const {
        if (node == nullptr) {
            return false;
        }
        char ch = key[index];
        if (ch < node->splitChar) {
            return searchHelper(node->left, key, index, outValue);
        } else if (ch > node->splitChar) {
            return searchHelper(node->right, key, index, outValue);
        } else {
            if (index + 1 < key.length()) {
                return searchHelper(node->mid, key, index + 1, outValue);
            } else {
                if (node->isEnd) {
                    outValue = node->value;
                    return true;
                }
                return false;
            }
        }
    }

    // Purpose: Recursive removal helper | Parameters: node (Node*), key (const std::string&), index (size_t), removed (bool&) | Return Value: Node* | Complexity: O(L)
    Node* removeHelper(Node* node, const std::string& key, size_t index, bool& removed) {
        if (node == nullptr) {
            removed = false;
            return nullptr;
        }
        char ch = key[index];
        if (ch < node->splitChar) {
            node->left = removeHelper(node->left, key, index, removed);
        } else if (ch > node->splitChar) {
            node->right = removeHelper(node->right, key, index, removed);
        } else {
            if (index + 1 < key.length()) {
                node->mid = removeHelper(node->mid, key, index + 1, removed);
            } else {
                if (node->isEnd) {
                    node->isEnd = false;
                    removed = true;
                    node->value = V();
                }
            }
        }

        if (!node->isEnd && node->left == nullptr && node->mid == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        return node;
    }

    // Purpose: Recursive node cleanup | Parameters: node (Node*) | Return Value: None | Complexity: O(N)
    void clearHelper(Node* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->mid);
            clearHelper(node->right);
            delete node;
        }
    }

    // Purpose: Recursive prefix collection | Parameters: node (Node*), currentPrefix (std::string), results (DynamicArray<V>&) | Return Value: None | Complexity: O(K) where K is number of matched nodes
    void collectPrefixHelper(Node* node, std::string currentPrefix, DynamicArray<V>& results) const {
        if (node == nullptr) {
            return;
        }
        collectPrefixHelper(node->left, currentPrefix, results);

        std::string midPrefix = currentPrefix + node->splitChar;
        if (node->isEnd) {
            results.push_back(node->value);
        }
        collectPrefixHelper(node->mid, midPrefix, results);

        collectPrefixHelper(node->right, currentPrefix, results);
    }

    // Purpose: Find node matching prefix exactly | Parameters: node (Node*), prefix (const std::string&), index (size_t) | Return Value: Node* | Complexity: O(L)
    Node* findNode(Node* node, const std::string& prefix, size_t index) const {
        if (node == nullptr) {
            return nullptr;
        }
        char ch = prefix[index];
        if (ch < node->splitChar) {
            return findNode(node->left, prefix, index);
        } else if (ch > node->splitChar) {
            return findNode(node->right, prefix, index);
        } else {
            if (index + 1 < prefix.length()) {
                return findNode(node->mid, prefix, index + 1);
            }
            return node;
        }
    }

    // Purpose: Recursive node cloning | Parameters: node (Node*) | Return Value: Node* | Complexity: O(N)
    Node* cloneHelper(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->splitChar);
        newNode->isEnd = node->isEnd;
        newNode->value = node->value;
        newNode->left = cloneHelper(node->left);
        newNode->mid = cloneHelper(node->mid);
        newNode->right = cloneHelper(node->right);
        return newNode;
    }

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    TernarySearchTree() : root(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~TernarySearchTree() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const TernarySearchTree&) | Return Value: None | Complexity: O(N)
    TernarySearchTree(const TernarySearchTree& other) : root(cloneHelper(other.root)), size(other.size) {}

    // Purpose: Copy Assignment Operator | Parameters: other (const TernarySearchTree&) | Return Value: TernarySearchTree& | Complexity: O(N)
    TernarySearchTree& operator=(const TernarySearchTree& other) {
        if (this != &other) {
            clear();
            root = cloneHelper(other.root);
            size = other.size;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (TernarySearchTree&&) | Return Value: None | Complexity: O(1)
    TernarySearchTree(TernarySearchTree&& other) noexcept : root(other.root), size(other.size) {
        other.root = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (TernarySearchTree&&) | Return Value: TernarySearchTree& | Complexity: O(1)
    TernarySearchTree& operator=(TernarySearchTree&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            size = other.size;
            other.root = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Insert string key associated with a value | Parameters: key (const std::string&), value (const V&) | Return Value: bool | Complexity: O(L)
    bool insert(const std::string& key, const V& value) {
        if (key.empty()) return false;
        bool inserted = false;
        root = insertHelper(root, key, 0, value, inserted);
        if (inserted) {
            size++;
        }
        return inserted;
    }

    // Purpose: Find value corresponding to string key | Parameters: key (const std::string&), outValue (V&) | Return Value: bool | Complexity: O(L)
    bool search(const std::string& key, V& outValue) const {
        if (key.empty()) return false;
        return searchHelper(root, key, 0, outValue);
    }

    // Purpose: Remove key-value entry from TST | Parameters: key (const std::string&) | Return Value: bool | Complexity: O(L)
    bool remove(const std::string& key) {
        if (key.empty()) return false;
        bool removed = false;
        root = removeHelper(root, key, 0, removed);
        if (removed) {
            size--;
        }
        return removed;
    }

    // Purpose: Find all values starting with a prefix | Parameters: prefix (const std::string&), results (DynamicArray<V>&) | Return Value: None | Complexity: O(L + K) where K matches
    void searchPrefix(const std::string& prefix, DynamicArray<V>& results) const {
        if (prefix.empty()) {
            collectPrefixHelper(root, "", results);
            return;
        }
        Node* node = findNode(root, prefix, 0);
        if (node == nullptr) {
            return;
        }
        if (node->isEnd) {
            results.push_back(node->value);
        }
        collectPrefixHelper(node->mid, prefix, results);
    }

    // Purpose: Check if TST is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Get number of unique keys | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Clear all nodes in TST | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        clearHelper(root);
        root = nullptr;
        size = 0;
    }
};

#endif // TERNARY_SEARCH_TREE_H
