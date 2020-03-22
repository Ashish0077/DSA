#include <iostream>
#include <list>
#include <unordered_map>
#include <hash_fun.h>
using namespace std;

template<typename K, typename V>
class HashTable {
    private:

        /*
            Entry Class
            This pairs the key and value together
            it computes the hash code of the key
        */
        class Entry {
            private:
                hash<K> hasher;

            public:
                int hashCode;
                K key;
                V value;
                
                Entry(K key, V value) {
                    this->key = key;
                    this->value = value;
                    this->hashCode = hasher(key);
                }

                bool operator==(const Entry &other) {
                    if (hashCode != other.hashCode)
                        return false;
                    return key == other.key;
                }

                bool operator!=(const Entry &other) {
                    if (hashCode != other.hashCode)
                        return true;
                    return key != other.key;
                }
        };

        // hash function for calculating hash
        hash<K> HASHER;
        // by default the capacity of the list will be 3
        const int DEFAULT_CAPACITY = 3;
        // by default the load factor will be 0.75
        const double DEFAULT_LOAD_FACTOR = 0.75;

        double maxLoadFactor;
        int capacity;
        int threshold;
        int _size;
        // this is the main table
        list<Entry> *table;

        int normalizeIndex(int hashCode) {
            int index = (hashCode & 0x7FFFFFFF) % capacity; 
            return index;
        }

        void init(int capacity, double maxLoadFactor) {
            if (capacity < 0) {
                throw invalid_argument("Illegal Capacity");
            }
            if (maxLoadFactor <= 0) {
                throw invalid_argument("Illegal Capacity");
            }
            this->maxLoadFactor = maxLoadFactor;
            this->capacity = max(DEFAULT_CAPACITY, capacity);
            threshold = (int) (this->capacity * maxLoadFactor);
            table = new list<Entry>[this->capacity];
            _size = 0;
        }

        void resizeTable() {
            int oldTableCapacity = capacity;
            capacity = capacity * 2;
            threshold = (int) (capacity * maxLoadFactor);
            list<Entry> *newTable = new list<Entry>[capacity];
            for(int i = 0; i < oldTableCapacity; i++) {
                list<Entry> bucket = table[i];
                for(auto it = bucket.begin(); it != bucket.end(); it++) {
                    int bucketIndex = normalizeIndex(it->hashCode);
                    newTable[bucketIndex].push_back(*it);
                }
            }
            delete[] table;
            table = newTable;
        }

    public:
        HashTable() {
            init(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
        }

        HashTable(int capacity) {
            init(capacity, DEFAULT_LOAD_FACTOR);
        }

        HashTable(int capacity, double maxLoadFactor) {
            init(capacity, maxLoadFactor);
        }

        void emplace(K key, V value) {
            Entry newEntry(key, value);
            int bucketIndex = normalizeIndex(newEntry.hashCode);
            list<Entry>* bucket = &table[bucketIndex];
            for(auto it = bucket->begin(); it != bucket->end(); it++) {
                if(*it == newEntry) {
                    it->value = newEntry.value;
                    return;
                }
            }
            bucket->push_back(newEntry);
            _size++;
            if (_size > threshold) {
                resizeTable();
            }
        }

        V operator[](const K key) {
            int bucketIndex = normalizeIndex(HASHER(key));
            list<Entry> bucket = table[bucketIndex];
            if(!bucket.empty()) {
                for(auto it = bucket.begin(); it != bucket.end(); it++) {
                    if (it->key == key) {
                        return it->value;
                    }
                }
            }
            return *(new V);
        }

        V getValue(const K key) {
            return this->operator[](key);
        }
};

int main() {
    HashTable<string, int> b;
    b.emplace("Mango", 1);
    b.emplace("Apple", 2);
    b.emplace("Grapes", 3);
    b.emplace("Pineapple", 4);
    return 0;
}