#include <iostream>
using namespace std;

template<typename T>
class DynamicArray {
    private:
        T* arr;
        int count;
        int _size;

    public:
        DynamicArray() {
            arr = new T[1];
            count = 0;  // points at the next index to insert element
            _size = 1; // actual size of the array (capacity)
        }

        ~DynamicArray() {
            delete[] arr;
        }

        class Iterator {
            private:
                const DynamicArray<T> *pArr;
                int index;
            public:
                Iterator(const DynamicArray<T> *arr, int i) {
                    pArr = arr;
                    index = i;
                }

                const T &operator*() const{
                    return pArr->operator[](index);
                }

                Iterator &operator++() {
                    index++;
                    return *this;
                }

                // overloading postfix operator (dummy parameter required)
                Iterator &operator++(int k) {
                    Iterator it(pArr, index);
                    index++;
                    return it;
                }

                bool operator!=(const Iterator &other) const {
                    return index != other.index;
                }

                bool operator==(const Iterator &other) const {
                    return index == other.index;
                }
        };

        Iterator begin() const{
            return Iterator(this, 0);
        }

        Iterator end() const{
            return Iterator(this , count);
        }

        // inserts at the back
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

        T &operator[](int i) const{
            return arr[i];
        }

        int capacity() const{
            return _size;
        }

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