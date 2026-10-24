#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>
#include <utility>
#include "DynamicArray.h"
#include "LinkedList.h"

// Purpose: A generic template Graph using an Adjacency List.
// Responsibilities: Model academic prerequisite dependencies, detect cycles, perform topological sorting.
// Data Structure Used: Adjacency List (implemented with custom DynamicArray and LinkedList)
// Time Complexity: Add Vertex: O(V), Add Edge: O(V), Search Edge: O(V + E) | Space Complexity: O(V + E)
// Dependencies: <cstddef>, <utility>, "DynamicArray.h", "LinkedList.h"
template <typename T>
class Graph {
public:
    struct Vertex {
        T id;
        LinkedList<T> neighbors;

        Vertex() = default;
        Vertex(const T& val) : id(val), neighbors() {}
    };

private:
    DynamicArray<Vertex> adjacencyList;

    // Purpose: Helper to find index of a vertexId | Parameters: vertexId (const T&) | Return Value: int | Complexity: O(V)
    int findVertexIndex(const T& vertexId) const {
        for (size_t i = 0; i < adjacencyList.getSize(); ++i) {
            if (adjacencyList[i].id == vertexId) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Purpose: Helper DFS for cycle detection | Parameters: vIndex (int), visited (DynamicArray<bool>&), recStack (DynamicArray<bool>&) | Return Value: bool | Complexity: O(V + E)
    bool isCyclicDFS(int vIndex, DynamicArray<bool>& visited, DynamicArray<bool>& recStack) const {
        visited[vIndex] = true;
        recStack[vIndex] = true;

        const LinkedList<T>& neighbors = adjacencyList[vIndex].neighbors;
        const typename LinkedList<T>::Node* current = neighbors.getHead();
        while (current != nullptr) {
            int neighborIdx = findVertexIndex(current->data);
            if (neighborIdx != -1) {
                if (!visited[neighborIdx]) {
                    if (isCyclicDFS(neighborIdx, visited, recStack)) {
                        return true;
                    }
                } else if (recStack[neighborIdx]) {
                    return true;
                }
            }
            current = current->next;
        }

        recStack[vIndex] = false;
        return false;
    }

    // Purpose: Helper DFS for topological sorting | Parameters: vIndex (int), visited (DynamicArray<bool>&), stack (DynamicArray<T>&) | Return Value: None | Complexity: O(V + E)
    void topologicalSortDFS(int vIndex, DynamicArray<bool>& visited, DynamicArray<T>& stack) const {
        visited[vIndex] = true;

        const LinkedList<T>& neighbors = adjacencyList[vIndex].neighbors;
        const typename LinkedList<T>::Node* current = neighbors.getHead();
        while (current != nullptr) {
            int neighborIdx = findVertexIndex(current->data);
            if (neighborIdx != -1 && !visited[neighborIdx]) {
                topologicalSortDFS(neighborIdx, visited, stack);
            }
            current = current->next;
        }

        stack.push_back(adjacencyList[vIndex].id);
    }

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Graph() : adjacencyList() {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(V)
    ~Graph() = default;

    // Purpose: Copy Constructor | Parameters: other (const Graph&) | Return Value: None | Complexity: O(V + E)
    Graph(const Graph& other) : adjacencyList(other.adjacencyList) {}

    // Purpose: Copy Assignment Operator | Parameters: other (const Graph&) | Return Value: Graph& | Complexity: O(V + E)
    Graph& operator=(const Graph& other) {
        if (this != &other) {
            adjacencyList = other.adjacencyList;
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (Graph&&) | Return Value: None | Complexity: O(1)
    Graph(Graph&& other) noexcept : adjacencyList(std::move(other.adjacencyList)) {}

    // Purpose: Move Assignment Operator | Parameters: other (Graph&&) | Return Value: Graph& | Complexity: O(1)
    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            adjacencyList = std::move(other.adjacencyList);
        }
        return *this;
    }

    // Purpose: Add a vertex to graph | Parameters: vertexId (const T&) | Return Value: bool | Complexity: O(V)
    bool addVertex(const T& vertexId) {
        if (findVertexIndex(vertexId) != -1) {
            return false;
        }
        adjacencyList.push_back(Vertex(vertexId));
        return true;
    }

    // Purpose: Add a directed edge from source to destination | Parameters: source (const T&), destination (const T&) | Return Value: bool | Complexity: O(V)
    bool addEdge(const T& source, const T& destination) {
        int srcIdx = findVertexIndex(source);
        int destIdx = findVertexIndex(destination);

        if (srcIdx == -1) {
            addVertex(source);
            srcIdx = findVertexIndex(source);
        }
        if (destIdx == -1) {
            addVertex(destination);
            destIdx = findVertexIndex(destination);
        }

        typename LinkedList<T>::Node* current = adjacencyList[srcIdx].neighbors.getHead();
        while (current != nullptr) {
            if (current->data == destination) {
                return false;
            }
            current = current->next;
        }

        adjacencyList[srcIdx].neighbors.push_back(destination);
        return true;
    }

    // Purpose: Remove a vertex and all its incident edges | Parameters: vertexId (const T&) | Return Value: bool | Complexity: O(V * E)
    bool removeVertex(const T& vertexId) {
        int idx = findVertexIndex(vertexId);
        if (idx == -1) {
            return false;
        }

        for (size_t i = 0; i < adjacencyList.getSize(); ++i) {
            adjacencyList[i].neighbors.remove(vertexId);
        }

        for (size_t i = idx; i + 1 < adjacencyList.getSize(); ++i) {
            adjacencyList[i] = std::move(adjacencyList[i + 1]);
        }
        adjacencyList.pop_back();
        return true;
    }

    // Purpose: Remove a directed edge from source to destination | Parameters: source (const T&), destination (const T&) | Return Value: bool | Complexity: O(V)
    bool removeEdge(const T& source, const T& destination) {
        int srcIdx = findVertexIndex(source);
        if (srcIdx == -1) {
            return false;
        }
        return adjacencyList[srcIdx].neighbors.remove(destination);
    }

    // Purpose: Check if a vertex exists | Parameters: vertexId (const T&) | Return Value: bool | Complexity: O(V)
    bool hasVertex(const T& vertexId) const {
        return findVertexIndex(vertexId) != -1;
    }

    // Purpose: Check if an edge exists from source to destination | Parameters: source (const T&), destination (const T&) | Return Value: bool | Complexity: O(V)
    bool hasEdge(const T& source, const T& destination) const {
        int srcIdx = findVertexIndex(source);
        if (srcIdx == -1) {
            return false;
        }
        const typename LinkedList<T>::Node* current = adjacencyList[srcIdx].neighbors.getHead();
        while (current != nullptr) {
            if (current->data == destination) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Purpose: Get neighbors of a vertex | Parameters: vertexId (const T&) | Return Value: const LinkedList<T>* | Complexity: O(V)
    const LinkedList<T>* getNeighbors(const T& vertexId) const {
        int idx = findVertexIndex(vertexId);
        if (idx == -1) {
            return nullptr;
        }
        return &(adjacencyList[idx].neighbors);
    }

    // Purpose: Get a list of all vertex IDs | Parameters: None | Return Value: DynamicArray<T> | Complexity: O(V)
    DynamicArray<T> getVertices() const {
        DynamicArray<T> vertices;
        for (size_t i = 0; i < adjacencyList.getSize(); ++i) {
            vertices.push_back(adjacencyList[i].id);
        }
        return vertices;
    }

    // Purpose: Perform topological sort on graph | Parameters: order (DynamicArray<T>&) | Return Value: bool (false if cycle detected) | Complexity: O(V + E)
    bool topologicalSort(DynamicArray<T>& order) const {
        if (isCyclic()) {
            return false;
        }

        size_t V = adjacencyList.getSize();
        DynamicArray<bool> visited(V);
        for (size_t i = 0; i < V; ++i) {
            visited.push_back(false);
        }

        DynamicArray<T> stack;
        for (size_t i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortDFS(static_cast<int>(i), visited, stack);
            }
        }

        order.clear();
        for (int i = static_cast<int>(stack.getSize()) - 1; i >= 0; --i) {
            order.push_back(stack[i]);
        }

        return true;
    }

    // Purpose: Detect if there is a cycle in graph | Parameters: None | Return Value: bool | Complexity: O(V + E)
    bool isCyclic() const {
        size_t V = adjacencyList.getSize();
        DynamicArray<bool> visited(V);
        DynamicArray<bool> recStack(V);
        for (size_t i = 0; i < V; ++i) {
            visited.push_back(false);
            recStack.push_back(false);
        }

        for (size_t i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (isCyclicDFS(static_cast<int>(i), visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Purpose: Clear all vertices and edges | Parameters: None | Return Value: None | Complexity: O(V)
    void clear() {
        adjacencyList.clear();
    }
};

#endif // GRAPH_H
