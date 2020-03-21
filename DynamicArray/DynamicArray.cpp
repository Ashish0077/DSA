#include <iostream>
using namespace std;

template<typename T>
class DynamicArray {
    private:
        // internal array pointer for dynamic allocation
        T* arr;
        int count;
        int _size;

    public:
        DynamicArray() {
            arr = new T[1]; // Intially the size of the array will be 1
            count = 0;  // points at the next index to insert element
            _size = 1; // actual size of the array (capacity)
        }

        ~DynamicArray() {
            delete[] arr;
        }

        /*
            Iterator Class:
            All functinality for iterating the array
        */
        class Iterator {
            private:
                const DynamicArray<T> *pArr;
                int index;
            public:
                Iterator(const DynamicArray<T> *arr, int i) {
                    pArr = arr;
                    index = i;
                }

                /*
                    Overloading * operator to make internal data accessible
                */
                const T &operator*() const{
                    return pArr->operator[](index);
                }

                /*
                    Overloading prefix ++ operator
                    this makes the iterator to move to next index
                */
                Iterator &operator++() {
                    index++;
                    return *this;
                }

                /*
                    Overloading postfixx ++ operator
                    this makes the iterator to move to next index
                */
                Iterator &operator++(int k) {
                    Iterator it(pArr, index);
                    index++;
                    return it;
                }

                /*
                    Overloading != operator
                    this is used for comparision
                    returns true when not equal else false
                */
                bool operator!=(const Iterator &other) const {
                    return index != other.index;
                }

                /*
                    Overlaading == operator
                    this is used for comparision
                    return true when equal else false
                */
                bool operator==(const Iterator &other) const {
                    return index == other.index;
                }
        };

        /*
            This function is used to get a Iterator
            from the begining of the array
            begin() and end() helps in implementing for-each loop
        */
        Iterator begin() const{
            return Iterator(this, 0);
        }
        
        /*
            This function is used to get a Iterator to end of the list
            begin() and end() helps in implementing for-each loop
        */
        Iterator end() const{
            return Iterator(this , count);
        }

        /*
            This function is used to insert elements
            at the back/end of the list
            Time Complexity : O(1) on average
            when the array reallocate its o(n)
        */
        void emplaceBack(const T &data) {
            // if array is full reallocating space
            if(count == _size) {
                _size = _size * 2;
                T* newArr = new T[_size];
                for(int i = 0; i < count; i++) {
                    newArr[i] = arr[i];
                }
                delete[] arr;
                arr = NULL;
                arr = newArr;
            }

            // emplacing data at the back
            arr[count] = data;
            count++;
        }

        // alternative to emplaceBack
        void pushBack(const T &data) {
            emplaceBack(data);
        }

        // remove elements from the back
        void popBack() {
            // count cant go negative
            if(count > 0)
                count--;
        }

        // returns the element at index i
        T at(int i) const{
            return arr[i];
        }

        // returns the element at index i
        T &operator[](int i) const{
            return arr[i];
        }

        // returns the orignal size of the array
        int capacity() const{
            return _size;
        }

        // returns the number of elements
        int size() const{
            return count;
        }

        // reserves memory for array
        void reserve(int &k) {
            _size = k;
            T* newArr = new T[_size];
            for(int i = 0; i < count; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }

};

int main() {

    // Test Code
    DynamicArray<int> a;
    cout << a.capacity() << endl;
    a.emplaceBack(2);
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << "capacity : " <<  a.capacity() << endl;
    a.pushBack(3);
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    a.popBack();
    cout << "capacity : " <<  a.capacity() << endl;
    a.pushBack(4);
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << "capacity : " <<  a.capacity() << endl;
    
    // testing iterator
    for (DynamicArray<int>::Iterator k = a.begin(); k != a.end(); ++k) {
        cout << *k << " ";
    }
    cout << "capacity : " <<  a.capacity() << endl;

    // testing range based loop
    for(auto it: a) {
        cout << it << " ";
    }
    
    return 0;
}