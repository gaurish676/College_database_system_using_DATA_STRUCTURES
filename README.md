# 🏛️ College Database & ERP System using Custom Data Structures

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)](Makefile)
[![Unit Tests](https://img.shields.io/badge/Tests-62%2F62%20Passing%20(100%25)-success.svg)](tests/test_datastructures.cpp)
[![STL Independent](https://img.shields.io/badge/STL%20Containers-Zero%20Used-orange.svg)](#-data-structures-implemented)
[![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)](LICENSE)

A high-performance, modular College ERP (Enterprise Resource Planning) and Database Management Engine written in modern **C++ (C++17)** from scratch. Built entirely without standard template containers like `std::vector`, `std::map`, or `std::list`, this engine relies exclusively on custom-built linear, non-linear, and hierarchical data structures for optimal algorithmic efficiency and binary file persistence.

---

## 🚀 Key Modules & System Capabilities

- **Authentication System**: Hashed password user verification with binary file persistence (`data/users.dat`).
- **Student Management**: Student records, GPA tracking, course enrollments using custom Doubly Linked Lists & Hash Tables.
- **Faculty Management**: Staff details, department assignments, and dynamic searching.
- **Fee & Billing Management**: Automatic fee calculation, bill generation, payment processing, and tracking.
- **Award & Recognition System**: Merit awards, student achievements, and dynamic reporting.
- **Advanced Search Engine**: Prefix search with Ternary Search Trees (TST), range queries with Heap/AVL Trees, and fast O(1) key lookups via Hash Tables.
- **Course Prerequisites & Dependencies**: Directed graph structure to represent course prerequisites and compute academic pathways via topological sorting.
- **Binary Serialization Engine**: Custom binary serialization/deserialization routines for state persistence (`Serializer` / `Deserializer`).

---

## 🛠️ Data Structures Implemented From Scratch

This project implements all foundational data structures without external libraries:

| Data Structure | Implementation File | Time Complexity | Usage in Project |
| :--- | :--- | :---: | :--- |
| **AVL Tree** | [`datastructures/AVLTree.h`](./datastructures/AVLTree.h) | $O(\log N)$ | Self-balancing BST for sorted indexing & range queries |
| **Ternary Search Tree (TST)** | [`datastructures/TernarySearchTree.h`](./datastructures/TernarySearchTree.h) | $O(L)$ | Fast prefix search (autocomplete) for names and courses |
| **Hash Table** | [`datastructures/HashTable.h`](./datastructures/HashTable.h) | $O(1)$ avg | O(1) average lookup for authentication & quick indexing |
| **Directed Graph** | [`datastructures/Graph.h`](./datastructures/Graph.h) | $O(V + E)$ | Prerequisites graph and academic pathway topological sort |
| **Heap (Priority Queue)** | [`datastructures/Heap.h`](./datastructures/Heap.h) | $O(\log N)$ | Max/Min heap for ranking students by GPA and merit |
| **Doubly Linked List** | [`datastructures/DoublyLinkedList.h`](./datastructures/DoublyLinkedList.h) | $O(1)$ insert | Sequential collection for main entity managers |
| **Dynamic Array** | [`datastructures/DynamicArray.h`](./datastructures/DynamicArray.h) | $O(1)$ amortized | Resizable arrays replacing `std::vector` |
| **Queue & Circular Queue** | [`datastructures/Queue.h`](./datastructures/Queue.h) | $O(1)$ | Task queues and billing workflow processing |
| **Stack** | [`datastructures/Stack.h`](./datastructures/Stack.h) | $O(1)$ | Undo history and menu navigation stack |

---

## 📂 Project Architecture

```text
College_database_system_using_DATA_STRUCTURES/
├── datastructures/      # Template header-only custom Data Structures
├── include/             # Header declarations for models, managers, and utilities
├── modules/             # C++ implementations for domain logic & management
├── storage/             # Binary serialization, file read/write engines
├── utils/               # Logger, Console Utilities, and Input Validation
├── tests/               # Automated unit test suite (62/62 passing)
├── data/                # Data storage directory (.dat binary files)
├── .github/workflows/   # Automated CI pipeline
├── main.cpp             # CLI Application Menu Entrypoint
├── Makefile             # Automated Build & Test System
├── .gitignore           # Git ignore rules for binaries and objects
└── README.md            # Project Documentation
```

---

## 🛠️ Build and Execution

### Prerequisites
- `g++` compiler supporting **C++17** standard
- `make` build utility

### 1. Build the Full Application
```bash
make clean
make
```

### 2. Run the Automated Unit Test Suite
```bash
make test
```
*Expected Output:*
```text
========================================================
  COLLEGE DATABASE SYSTEM — AUTOMATED UNIT TEST SUITE   
========================================================

Running DynamicArray tests...
Running LinkedList & DoublyLinkedList tests...
Running Stack & Queue tests...
Running AVLTree (Self-Balancing BST) tests...
Running TernarySearchTree (Prefix Search / Autocomplete) tests...
Running HashTable tests...
Running Heap (Priority Queue) tests...
Running Graph (Course Prerequisite Engine) tests...

--------------------------------------------------------
TEST SUMMARY: 62 / 62 assertions passed.
ALL UNIT TESTS PASSED SUCCESSFULLY! (100% GREEN)
```

### 3. Run the CLI Dashboard
```bash
./college_erp
```

> **Default Login Credentials**:  
> Username: `admin`  
> Password: `admin123`

---

## 📤 Pushing to GitHub

To publish these updates to your GitHub repository ([`gaurish676/College_database_system_using_DATA_STRUCTURES`](https://github.com/gaurish676/College_database_system_using_DATA_STRUCTURES)):

```bash
git add .
git commit -m "feat: complete C++17 custom data structures engine with unit tests and CI"
git push -u origin main
```

---

## 📝 License
This project is open-source under the MIT License.
