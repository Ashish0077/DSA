#include <iostream>
#include <vector>

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

        // inserts at the back
        void emplaceBack(const T data) {
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
        void pushBack(const T data) {
            emplaceBack(data);
        }

        // remove elements from the back
        void popBack() {
            // count cant go negative
            if(count > 0)
                count--;
        }

        T operator[](int i) {
            return arr[i];
        }

        int capacity() {
            return _size;
        }

        int size() {
            return count;
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
    return 0;
}