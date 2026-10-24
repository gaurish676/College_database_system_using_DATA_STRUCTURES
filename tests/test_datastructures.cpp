/**
 * Comprehensive Automated Unit Test Suite for Custom Data Structures
 * College Database & ERP System
 * Zero External Test Framework Dependencies - Pure C++17
 */

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "datastructures/DynamicArray.h"
#include "datastructures/LinkedList.h"
#include "datastructures/DoublyLinkedList.h"
#include "datastructures/Stack.h"
#include "datastructures/Queue.h"
#include "datastructures/CircularQueue.h"
#include "datastructures/AVLTree.h"
#include "datastructures/TernarySearchTree.h"
#include "datastructures/HashTable.h"
#include "datastructures/Heap.h"
#include "datastructures/Graph.h"

// ANSI Color formatting
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int total_tests = 0;
int passed_tests = 0;

#define TEST_ASSERT(cond, msg) \
    do { \
        total_tests++; \
        if (cond) { \
            passed_tests++; \
        } else { \
            std::cerr << RED << "  [FAILED] " << msg << " (line " << __LINE__ << ")" << RESET << std::endl; \
        } \
    } while (0)

void test_dynamic_array() {
    std::cout << CYAN << "Running DynamicArray tests..." << RESET << std::endl;
    DynamicArray<int> arr;
    TEST_ASSERT(arr.isEmpty(), "DynamicArray should initially be empty");
    TEST_ASSERT(arr.getSize() == 0, "DynamicArray initial size should be 0");

    for (int i = 0; i < 50; ++i) {
        arr.push_back(i * 10);
    }
    TEST_ASSERT(arr.getSize() == 50, "Size should be 50 after 50 push_backs");
    TEST_ASSERT(arr[0] == 0, "Index 0 should be 0");
    TEST_ASSERT(arr[49] == 490, "Index 49 should be 490");

    arr.pop_back();
    TEST_ASSERT(arr.getSize() == 49, "Size should be 49 after pop_back()");
    TEST_ASSERT(arr[arr.getSize() - 1] == 480, "Last element should be 480");

    arr.clear();
    TEST_ASSERT(arr.isEmpty(), "Array should be empty after clear()");
}

void test_linked_list() {
    std::cout << CYAN << "Running LinkedList & DoublyLinkedList tests..." << RESET << std::endl;
    LinkedList<std::string> sList;
    sList.push_back("Alpha");
    sList.push_back("Beta");
    sList.push_front("Pre-Alpha");
    TEST_ASSERT(sList.getSize() == 3, "LinkedList size should be 3");

    DoublyLinkedList<int> dList;
    dList.push_back(100);
    dList.push_back(200);
    dList.push_front(50);
    TEST_ASSERT(dList.getSize() == 3, "DoublyLinkedList size should be 3");
    
    TEST_ASSERT(dList.remove(100), "Remove 100 should succeed");
    TEST_ASSERT(dList.getSize() == 2, "Size should be 2 after removing 100");
    TEST_ASSERT(!dList.remove(999), "Removing non-existent element should return false");
}

void test_stack_and_queue() {
    std::cout << CYAN << "Running Stack & Queue tests..." << RESET << std::endl;
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    TEST_ASSERT(st.top() == 3, "Top of stack should be 3");
    TEST_ASSERT(st.pop(), "Pop 3 should succeed");
    TEST_ASSERT(st.top() == 2, "New top should be 2");
    TEST_ASSERT(st.getSize() == 2, "Stack size should be 2");

    Queue<std::string> q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");
    TEST_ASSERT(q.front() == "first", "Queue front should be 'first'");
    TEST_ASSERT(q.dequeue(), "Dequeue should succeed");
    TEST_ASSERT(q.front() == "second", "New queue front should be 'second'");

    CircularQueue<int> cq(5);
    TEST_ASSERT(cq.enqueue(10), "Enqueue 10 should succeed");
    TEST_ASSERT(cq.enqueue(20), "Enqueue 20 should succeed");
    TEST_ASSERT(cq.front() == 10, "CircularQueue front should be 10");
    TEST_ASSERT(cq.dequeue(), "Dequeue should succeed");
    TEST_ASSERT(cq.front() == 20, "CircularQueue new front should be 20");
}

void test_avl_tree() {
    std::cout << CYAN << "Running AVLTree (Self-Balancing BST) tests..." << RESET << std::endl;
    AVLTree<int, std::string> avl;
    TEST_ASSERT(avl.isEmpty(), "AVLTree should initially be empty");

    // Insert strictly increasing values (triggers Left/Right rotations to maintain O(log N) balance)
    for (int i = 1; i <= 15; ++i) {
        avl.insert(i, "val_" + std::to_string(i));
    }
    TEST_ASSERT(avl.getSize() == 15, "AVLTree size should be 15");

    std::string foundVal;
    TEST_ASSERT(avl.search(7, foundVal) && foundVal == "val_7", "Search key 7 should return 'val_7'");
    TEST_ASSERT(avl.search(15, foundVal) && foundVal == "val_15", "Search key 15 should return 'val_15'");
    TEST_ASSERT(!avl.search(99, foundVal), "Search non-existent key 99 should fail");

    // Deletion
    TEST_ASSERT(avl.remove(7), "Remove key 7 should succeed");
    TEST_ASSERT(avl.getSize() == 14, "Size should be 14 after deletion");
    TEST_ASSERT(!avl.search(7, foundVal), "Key 7 should no longer be found");
}

void test_ternary_search_tree() {
    std::cout << CYAN << "Running TernarySearchTree (Prefix Search / Autocomplete) tests..." << RESET << std::endl;
    TernarySearchTree<std::string> tst;
    tst.insert("apple", "Fruit: Apple");
    tst.insert("application", "Software: Application");
    tst.insert("applet", "Java: Applet");
    tst.insert("banana", "Fruit: Banana");
    tst.insert("band", "Music: Band");

    std::string outVal;
    TEST_ASSERT(tst.search("apple", outVal) && outVal == "Fruit: Apple", "Exact search 'apple' should match");
    TEST_ASSERT(!tst.search("appl", outVal), "Incomplete prefix 'appl' should not match exact search");

    DynamicArray<std::string> prefixResults;
    tst.searchPrefix("app", prefixResults);
    TEST_ASSERT(prefixResults.getSize() == 3, "Prefix 'app' should match exactly 3 entries (apple, application, applet)");

    DynamicArray<std::string> banResults;
    tst.searchPrefix("ban", banResults);
    TEST_ASSERT(banResults.getSize() == 2, "Prefix 'ban' should match 2 entries (banana, band)");

    TEST_ASSERT(tst.remove("apple"), "Remove 'apple' should succeed");
    TEST_ASSERT(!tst.search("apple", outVal), "'apple' should be removed");

    DynamicArray<std::string> postRemoveResults;
    tst.searchPrefix("app", postRemoveResults);
    TEST_ASSERT(postRemoveResults.getSize() == 2, "Prefix 'app' should now match 2 entries");
}

void test_hash_table() {
    std::cout << CYAN << "Running HashTable tests..." << RESET << std::endl;
    HashTable<std::string, int> table(8);
    table.insert("Alice", 95);
    table.insert("Bob", 88);
    table.insert("Charlie", 92);
    table.insert("David", 78);
    table.insert("Eve", 85);

    int score = 0;
    TEST_ASSERT(table.search("Alice", score) && score == 95, "Alice's score should be 95");
    TEST_ASSERT(table.search("Charlie", score) && score == 92, "Charlie's score should be 92");
    TEST_ASSERT(!table.search("Unknown", score), "Non-existent key should not be found");

    // Removal and Tombstone handling
    TEST_ASSERT(table.remove("Bob"), "Remove 'Bob' should succeed");
    TEST_ASSERT(!table.search("Bob", score), "'Bob' should not be found after removal");
    TEST_ASSERT(table.search("Charlie", score) && score == 92, "Charlie should still be found past tombstone");

    // Dynamic Rehashing
    for (int i = 0; i < 30; ++i) {
        table.insert("user_" + std::to_string(i), i * 10);
    }
    TEST_ASSERT(table.getSize() > 30, "Table should dynamically rehash and store all items");
    TEST_ASSERT(table.search("user_25", score) && score == 250, "User 25 should be retrieved after rehashing");
}

void test_heap() {
    std::cout << CYAN << "Running Heap (Priority Queue) tests..." << RESET << std::endl;
    // Default Heap is Max-Heap using Less comparator
    Heap<int> maxHeap;
    maxHeap.insert(20);
    maxHeap.insert(50);
    maxHeap.insert(10);
    maxHeap.insert(40);
    maxHeap.insert(30);

    TEST_ASSERT(maxHeap.peek() == 50, "Max-Heap root should be 50");

    int extracted = 0;
    std::vector<int> expected = {50, 40, 30, 20, 10};
    for (int exp : expected) {
        TEST_ASSERT(maxHeap.extractTop(extracted) && extracted == exp, 
                    ("Extracted " + std::to_string(extracted) + " should equal " + std::to_string(exp)).c_str());
    }
    TEST_ASSERT(maxHeap.isEmpty(), "Heap should be empty after extracting all elements");

    // Min-Heap using custom Greater comparator
    struct Greater {
        bool operator()(const int& a, const int& b) const { return a > b; }
    };
    Heap<int, Greater> minHeap;
    minHeap.insert(35);
    minHeap.insert(15);
    minHeap.insert(25);
    TEST_ASSERT(minHeap.peek() == 15, "Min-Heap root should be 15");
}

void test_graph() {
    std::cout << CYAN << "Running Graph (Course Prerequisite Engine) tests..." << RESET << std::endl;
    Graph<std::string> g;
    g.addVertex("CS101");
    g.addVertex("CS102");
    g.addVertex("CS201");
    g.addVertex("CS301");

    // CS101 -> CS102 -> CS201 -> CS301 (Acyclic)
    g.addEdge("CS101", "CS102");
    g.addEdge("CS102", "CS201");
    g.addEdge("CS201", "CS301");

    TEST_ASSERT(g.hasEdge("CS101", "CS102"), "Edge CS101 -> CS102 should exist");
    TEST_ASSERT(!g.hasEdge("CS101", "CS301"), "Direct edge CS101 -> CS301 should not exist");
    TEST_ASSERT(!g.isCyclic(), "Linear prerequisite chain should be acyclic");

    DynamicArray<std::string> topoOrder;
    bool hasOrder = g.topologicalSort(topoOrder);
    TEST_ASSERT(hasOrder, "Topological sort on DAG should succeed");
    TEST_ASSERT(topoOrder.getSize() == 4, "Topological sort should contain all 4 courses");

    // Introduce cycle: CS301 -> CS101
    g.addEdge("CS301", "CS101");
    TEST_ASSERT(g.isCyclic(), "Graph with circular dependency should be cyclic");
}

int main() {
    std::cout << BOLD << "\n========================================================" << std::endl;
    std::cout << "  COLLEGE DATABASE SYSTEM — AUTOMATED UNIT TEST SUITE   " << std::endl;
    std::cout << "========================================================\n" << RESET << std::endl;

    test_dynamic_array();
    test_linked_list();
    test_stack_and_queue();
    test_avl_tree();
    test_ternary_search_tree();
    test_hash_table();
    test_heap();
    test_graph();

    std::cout << BOLD << "\n--------------------------------------------------------" << std::endl;
    std::cout << "TEST SUMMARY: " << passed_tests << " / " << total_tests << " assertions passed." << RESET << std::endl;

    if (passed_tests == total_tests) {
        std::cout << GREEN << BOLD << "ALL UNIT TESTS PASSED SUCCESSFULLY! (100% GREEN)\n" << RESET << std::endl;
        return 0;
    } else {
        std::cout << RED << BOLD << "SOME TESTS FAILED! (" << (total_tests - passed_tests) << " failures)\n" << RESET << std::endl;
        return 1;
    }
}
