#include <iostream>
#include <list>
#include <hash_fun.h>
using namespace std;

template<typename T>
class HashSet {
    private:

        class Entry {
            private:
                hash<T> hasher;
            public:
                int hashCode;
                T value;

                Entry(T value) {
                    this->value = value;
                    this->hashCode = hasher(value);
                }

                bool operator==(const Entry &other) {
                    return hashCode == other.hashCode;
                }

                bool operator!=(const Entry &other) {
                    return hashCode != other.hashCode;
                }
        };

        const int DEFAULT_CAPACITY = 3;
        const double DEFAULT_LOAD_FACTOR = 0.75;

        hash<T> HASHER;
        int _size;
        int capacity;
        double maxLoadFactor;
        int threshold;

        list<Entry>* table;

        /*
            This function is used initialize the private
            variables (it have the common functionality of constructor)
        */
        void init(int capacity, double maxLoadFactor) {
            if (capacity <= 0) {
                throw invalid_argument("Illegal Capacity");
            }

            if (maxLoadFactor <= 0) {
                throw invalid_argument("Illegal Capacity");
            }

            this->capacity = max(capacity, DEFAULT_CAPACITY);
            this->maxLoadFactor = maxLoadFactor;
            threshold = (int) (this->capacity * maxLoadFactor);
            table = new list<Entry>[this->capacity];
            _size = 0;
        }

        /*  
            This function is used to convert the hashcode
            to index It removes the -ve sign and then mod it with capcity
            Time Complexity: O(1)
        */
        int normalizeIndex(int hashCode) {
            return (hashCode & INT32_MAX) % capacity;
        }

        /*
            This function is used for increasing the size of table
            when required. It doubles the capacity. and then rehashes
            the elements to the new table
            Time Complexity: O(n) 
        */
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
            // cout << "Resized new Capacity : " << capacity << endl;
        }

    public:
        HashSet() {
            init(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
        }

        HashSet(int capacity) {
            init(capacity, DEFAULT_LOAD_FACTOR);
        }

        HashSet(int capacity, double maxLoadFactor) {
            init(capacity, maxLoadFactor);
        }
        /*
            class Iterator {
            private:
                typename list<Entry>::iterator it;
                list<Entry>* table;
                list<Entry> bucket;
                int capacity;
                int index;
            public:
                Iterator(list<Entry>* table, int capacity, bool e) {
                    this->table = table;
                    if(!e) {
                        this->capacity = capacity;
                        index = 0;
                        bucket = table[index];
                        it = bucket.begin();
                    } else {
                        bucket = table[capacity - 1];
                        it = bucket.end();
                    }
                }

                T operator*() {
                    return it->value;
                }

                Iterator operator++() {
                    it++;
                    if(it == bucket.end()) {
                        index++;
                        if(index >= capacity) {
                            bucket = table[capacity - 1];
                            it = bucket.end();
                        } else {
                            bucket = table[index];
                            it = bucket.begin();
                        }
                    }
                    return *this;
                }

                Iterator operator++(int k) {
                    it++;
                    if(it == bucket.end()) {
                        index++;
                        if(index >= capacity) {
                            bucket = table[capacity - 1];
                            it = bucket.end();
                        } else {
                            bucket = table[index];
                            it = bucket.begin();
                        }
                    }
                    return *this;
                }

                bool operator==(const Iterator &other) {
                    return it == other.it;
                }

                bool operator!=(const Iterator &other) {
                    return it != other.it;
                }
            };

            Iterator begin() {
                return Iterator(table, capacity, false);
            }

            Iterator end() {
                return Iterator(table, capacity, true);
            }
        */

        /*
            This function is used to insert the value
            in the set
            time complexity : O(1)
        */
        void emplace(T value) {
            Entry newEntry(value);
            int bucketIndex = normalizeIndex(newEntry.hashCode);
            list<Entry>* bucket = &table[bucketIndex];
            if(!bucket->empty()) {
                for(auto it = bucket->begin(); it != bucket->end(); it++) {
                    if (it->value == value) {
                        return;
                    }
                }
            }
            bucket->emplace_back(newEntry);
            _size++;
            if(_size > threshold) {
                resizeTable();
            }
        }

        /*
            This function is used to remove the provided
            value from the set
        */
        void remove(T value) {
            int bucketIndex = normalizeIndex(HASHER(value));
            list<Entry>* bucket = &table[bucketIndex];
            for(auto it = bucket->begin(); it != bucket->end(); it++) {
                if(it->value == value) {
                    bucket->erase(it);
                    _size--;
                    break;
                }
            }
        }

        bool contains(T value) {
            int bucketIndex = normalizeIndex(HASHER(value));
            list<Entry>* bucket = &table[bucketIndex];
            for(auto it: *bucket) {
                if (it.value = value) {
                    return true;
                }
            }
            return false;
        }

        /*
            This function is used to get all the values
            available in the set
        */
        list<T> getValues() {
            list<T>* newList = new list<T>;
            for(int i = 0; i < capacity; i++) {
                list<Entry>* bucket = &table[i];
                for(auto it = bucket->begin(); it != bucket->end(); it++) {
                    newList->push_back(it->value);
                }
            }
            return *newList;
        }

        /*  
            This function is used to print the 
            internal buckets of the hashTable
        */
        // void printBuckets() {
        //     for(int i = 0; i < capacity; i++) {
        //         list<Entry>* bucket = &table[i];
        //         cout << i << " : ";
        //         for(auto it: *bucket) {
        //             cout << it.value << " -> ";
        //         }
        //         cout << "NULL" << endl;
        //     }
        // }
}; 

int main() {

    HashSet<int> a;
    a.emplace(100);
    a.emplace(252);
    a.emplace(87);
    a.emplace(87);
    a.emplace(98);
    a.emplace(98);
    a.emplace(98);
    a.emplace(254);
    a.emplace(254);
    a.emplace(254);

    auto values = a.getValues();
    for(auto it: values) {
        cout << it << " ";
    }
    return 0;
}