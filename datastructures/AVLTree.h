#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <algorithm>
#include <utility>

// Purpose: A generic self-balancing Binary Search Tree (AVL Tree).
// Responsibilities: Maintains balanced height, inserts, deletes, and searches key-value pairs efficiently.
// Data Structure Used: AVL Balanced BST
// Time Complexity: Search/Insert/Delete: O(log N) | Space Complexity: O(N)
// Dependencies: <cstddef>, <algorithm>, <utility>
template <typename K, typename V>
class AVLTree {
public:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;

        Node(const K& k, const V& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

private:
    Node* root;
    size_t size;

    // Purpose: Helper to get height of a node | Parameters: node (Node*) | Return Value: int | Complexity: O(1)
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    // Purpose: Helper to get balance factor of a node | Parameters: node (Node*) | Return Value: int | Complexity: O(1)
    int getBalanceFactor(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Purpose: Helper to update height of a node | Parameters: node (Node*) | Return Value: None | Complexity: O(1)
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Purpose: Right rotation helper | Parameters: y (Node*) | Return Value: Node* | Complexity: O(1)
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Purpose: Left rotation helper | Parameters: x (Node*) | Return Value: Node* | Complexity: O(1)
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Purpose: Balance node balancing height | Parameters: node (Node*) | Return Value: Node* | Complexity: O(1)
    Node* balanceNode(Node* node) {
        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    // Purpose: Recursive insertion helper | Parameters: node (Node*), key (const K&), value (const V&), inserted (bool&) | Return Value: Node* | Complexity: O(log N)
    Node* insertHelper(Node* node, const K& key, const V& value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(key, value);
        }
        if (key < node->key) {
            node->left = insertHelper(node->left, key, value, inserted);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value, inserted);
        } else {
            node->value = value;
            inserted = false;
            return node;
        }
        return balanceNode(node);
    }

    // Purpose: Find node with minimum value | Parameters: node (Node*) | Return Value: Node* | Complexity: O(log N)
    Node* findMinValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Purpose: Recursive removal helper | Parameters: node (Node*), key (const K&), removed (bool&) | Return Value: Node* | Complexity: O(log N)
    Node* removeHelper(Node* node, const K& key, bool& removed) {
        if (node == nullptr) {
            removed = false;
            return nullptr;
        }
        if (key < node->key) {
            node->left = removeHelper(node->left, key, removed);
        } else if (key > node->key) {
            node->right = removeHelper(node->right, key, removed);
        } else {
            removed = true;
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = findMinValueNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = removeHelper(node->right, temp->key, removed);
            }
        }
        return balanceNode(node);
    }

    // Purpose: Recursive search helper | Parameters: node (Node*), key (const K&) | Return Value: Node* | Complexity: O(log N)
    Node* searchHelper(Node* node, const K& key) const {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }

    // Purpose: Recursive deletion of nodes | Parameters: node (Node*) | Return Value: None | Complexity: O(N)
    void clearHelper(Node* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    // Purpose: Recursive cloning of nodes | Parameters: node (Node*) | Return Value: Node* | Complexity: O(N)
    Node* cloneHelper(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->key, node->value);
        newNode->left = cloneHelper(node->left);
        newNode->right = cloneHelper(node->right);
        newNode->height = node->height;
        return newNode;
    }

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    AVLTree() : root(nullptr), size(0) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~AVLTree() {
        clear();
    }

    // Purpose: Copy Constructor | Parameters: other (const AVLTree&) | Return Value: None | Complexity: O(N)
    AVLTree(const AVLTree& other) : root(cloneHelper(other.root)), size(other.size) {}

    // Purpose: Copy Assignment Operator | Parameters: other (const AVLTree&) | Return Value: AVLTree& | Complexity: O(N)
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clear();
            root = cloneHelper(other.root);
            size = other.size;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (AVLTree&&) | Return Value: None | Complexity: O(1)
    AVLTree(AVLTree&& other) noexcept : root(other.root), size(other.size) {
        other.root = nullptr;
        other.size = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (AVLTree&&) | Return Value: AVLTree& | Complexity: O(1)
    AVLTree& operator=(AVLTree&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            size = other.size;
            other.root = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Purpose: Insert key-value pair into AVL tree | Parameters: key (const K&), value (const V&) | Return Value: bool | Complexity: O(log N)
    bool insert(const K& key, const V& value) {
        bool inserted = false;
        root = insertHelper(root, key, value, inserted);
        if (inserted) {
            size++;
        }
        return inserted;
    }

    // Purpose: Remove key-value pair from AVL tree | Parameters: key (const K&) | Return Value: bool | Complexity: O(log N)
    bool remove(const K& key) {
        bool removed = false;
        root = removeHelper(root, key, removed);
        if (removed) {
            size--;
        }
        return removed;
    }

    // Purpose: Find value corresponding to key | Parameters: key (const K&), outValue (V&) | Return Value: bool | Complexity: O(log N)
    bool search(const K& key, V& outValue) const {
        Node* node = searchHelper(root, key);
        if (node) {
            outValue = node->value;
            return true;
        }
        return false;
    }

    // Purpose: Check if AVL tree is empty | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isEmpty() const {
        return size == 0;
    }

    // Purpose: Get number of nodes in AVL tree | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Clear all nodes | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        clearHelper(root);
        root = nullptr;
        size = 0;
    }

    // Purpose: Get pointer to the root node (for traversals) | Parameters: None | Return Value: Node* | Complexity: O(1)
    Node* getRoot() {
        return root;
    }

    // Purpose: Get pointer to the root node (const) | Parameters: None | Return Value: const Node* | Complexity: O(1)
    const Node* getRoot() const {
        return root;
    }
};

#endif // AVL_TREE_H
