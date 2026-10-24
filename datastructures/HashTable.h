#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

enum class EntryState : uint8_t {
    EMPTY = 0,
    ACTIVE = 1,
    TOMBSTONE = 2 // Serves as the unique Tombstone Identifier value (preserving lookup chain integrity)
};

template <typename T>
struct HashHelper {
    // Purpose: Static hash fallback for primitive values | Parameters: val (const T&) | Return Value: size_t | Complexity: O(1)
    static size_t hash(const T& val) {
        return static_cast<size_t>(val);
    }
};

// Specialization for std::string keys (djb2 hash)
template <>
struct HashHelper<std::string> {
    // Purpose: djb2 hashing algorithm for std::string | Parameters: val (const std::string&) | Return Value: size_t | Complexity: O(L) where L is string length
    static size_t hash(const std::string& val) {
        size_t h = 5381;
        for (char c : val) {
            h = ((h << 5) + h) + c;
        }
        return h;
    }
};

// Purpose: A generic template Hash Table with open addressing and linear probing.
// Responsibilities: Hash keys, probe for locations, handle inserts, lookups, and deletions with tombstones.
// Data Structure Used: Closed Hash Table (Array with Linear Probing)
// Time Complexity: Search/Insert/Delete: Average O(1), Worst O(N) | Space Complexity: O(N)
// Dependencies: <cstddef>, <cstdint>, <string>, <utility>
template <typename K, typename V>
class HashTable {
public:
    struct Entry {
        K key;
        V value;
        EntryState state;

        Entry() : state(EntryState::EMPTY) {}
    };

private:
    Entry* table;
    size_t capacity;
    size_t size;
    size_t tombstoneCount;
    float maxLoadFactor;

    // Purpose: Hash function mapping key to slot | Parameters: key (const K&) | Return Value: size_t | Complexity: O(1)
    size_t hashFunction(const K& key) const {
        if (capacity == 0) return 0;
        return HashHelper<K>::hash(key) % capacity;
    }

    // Purpose: Resize and rehash table contents | Parameters: newCapacity (size_t) | Return Value: None | Complexity: O(N)
    void rehash(size_t newCapacity) {
        Entry* oldTable = table;
        size_t oldCapacity = capacity;

        capacity = newCapacity;
        table = new Entry[capacity];
        size = 0;
        tombstoneCount = 0;

        for (size_t i = 0; i < oldCapacity; ++i) {
            if (oldTable[i].state == EntryState::ACTIVE) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
        delete[] oldTable;
    }

public:
    // Purpose: Constructor | Parameters: initialCapacity (size_t) | Return Value: None | Complexity: O(N)
    explicit HashTable(size_t initialCapacity = 16)
        : table(new Entry[initialCapacity]), capacity(initialCapacity), size(0), tombstoneCount(0), maxLoadFactor(0.7f) {}

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(N)
    ~HashTable() {
        delete[] table;
    }

    // Purpose: Copy Constructor | Parameters: other (const HashTable&) | Return Value: None | Complexity: O(N)
    HashTable(const HashTable& other)
        : table(new Entry[other.capacity]), capacity(other.capacity), size(other.size), tombstoneCount(other.tombstoneCount), maxLoadFactor(other.maxLoadFactor) {
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = other.table[i];
        }
    }

    // Purpose: Copy Assignment Operator | Parameters: other (const HashTable&) | Return Value: HashTable& | Complexity: O(N)
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete[] table;
            capacity = other.capacity;
            size = other.size;
            tombstoneCount = other.tombstoneCount;
            maxLoadFactor = other.maxLoadFactor;
            table = new Entry[capacity];
            for (size_t i = 0; i < capacity; ++i) {
                table[i] = other.table[i];
            }
        }
        return *this;
    }

    // Purpose: Move Constructor | Parameters: other (HashTable&&) | Return Value: None | Complexity: O(1)
    HashTable(HashTable&& other) noexcept
        : table(other.table), capacity(other.capacity), size(other.size), tombstoneCount(other.tombstoneCount), maxLoadFactor(other.maxLoadFactor) {
        other.table = nullptr;
        other.capacity = 0;
        other.size = 0;
        other.tombstoneCount = 0;
    }

    // Purpose: Move Assignment Operator | Parameters: other (HashTable&&) | Return Value: HashTable& | Complexity: O(1)
    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            delete[] table;
            table = other.table;
            capacity = other.capacity;
            size = other.size;
            tombstoneCount = other.tombstoneCount;
            maxLoadFactor = other.maxLoadFactor;
            other.table = nullptr;
            other.capacity = 0;
            other.size = 0;
            other.tombstoneCount = 0;
        }
        return *this;
    }

    // Purpose: Insert or update key-value pair | Parameters: key (const K&), value (const V&) | Return Value: bool | Complexity: Average O(1), Worst O(N)
    bool insert(const K& key, const V& value) {
        if (capacity == 0) return false;
        if (static_cast<float>(size + tombstoneCount) / capacity >= maxLoadFactor) {
            rehash(capacity == 0 ? 1 : capacity * 2);
        }

        size_t index = hashFunction(key);
        size_t start = index;
        size_t tombstoneIdx = capacity;
        bool foundTombstone = false;

        do {
            if (table[index].state == EntryState::EMPTY) {
                size_t insertIdx = foundTombstone ? tombstoneIdx : index;
                table[insertIdx].key = key;
                table[insertIdx].value = value;
                table[insertIdx].state = EntryState::ACTIVE;
                if (foundTombstone) {
                    tombstoneCount--;
                }
                size++;
                return true;
            } else if (table[index].state == EntryState::ACTIVE) {
                if (table[index].key == key) {
                    table[index].value = value;
                    return true;
                }
            } else if (table[index].state == EntryState::TOMBSTONE) {
                if (!foundTombstone) {
                    tombstoneIdx = index;
                    foundTombstone = true;
                }
            }
            index = (index + 1) % capacity;
        } while (index != start);

        if (foundTombstone) {
            table[tombstoneIdx].key = key;
            table[tombstoneIdx].value = value;
            table[tombstoneIdx].state = EntryState::ACTIVE;
            tombstoneCount--;
            size++;
            return true;
        }

        return false;
    }

    // Purpose: Find value corresponding to key | Parameters: key (const K&), outValue (V&) | Return Value: bool | Complexity: Average O(1), Worst O(N)
    bool search(const K& key, V& outValue) const {
        if (capacity == 0) return false;
        size_t index = hashFunction(key);
        size_t start = index;
        do {
            if (table[index].state == EntryState::EMPTY) {
                return false;
            } else if (table[index].state == EntryState::ACTIVE) {
                if (table[index].key == key) {
                    outValue = table[index].value;
                    return true;
                }
            }
            index = (index + 1) % capacity;
        } while (index != start);
        return false;
    }

    // Purpose: Remove key-value pair | Parameters: key (const K&) | Return Value: bool | Complexity: Average O(1), Worst O(N)
    bool remove(const K& key) {
        if (capacity == 0) return false;
        size_t index = hashFunction(key);
        size_t start = index;
        do {
            if (table[index].state == EntryState::EMPTY) {
                return false;
            } else if (table[index].state == EntryState::ACTIVE) {
                if (table[index].key == key) {
                    table[index].state = EntryState::TOMBSTONE;
                    size--;
                    tombstoneCount++;
                    return true;
                }
            }
            index = (index + 1) % capacity;
        } while (index != start);
        return false;
    }

    // Purpose: Get pointer to internal table | Parameters: None | Return Value: const Entry* | Complexity: O(1)
    const Entry* getTable() const {
        return table;
    }

    // Purpose: Get number of active entries | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getSize() const {
        return size;
    }

    // Purpose: Get current hash table capacity | Parameters: None | Return Value: size_t | Complexity: O(1)
    size_t getCapacity() const {
        return capacity;
    }

    // Purpose: Clear all entries | Parameters: None | Return Value: None | Complexity: O(N)
    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            table[i].state = EntryState::EMPTY;
        }
        size = 0;
        tombstoneCount = 0;
    }
};

#endif // HASH_TABLE_H
