#include <iostream>
using namespace std;

template<typename T>
class DynamicArray {
    private:
        T* arr;
        int count;
        int size;

    public:
        DynamicArray() {
            T* arr = new T[1];
            count = 0;
            size = 1;
        }

        void insert(const int data) {
            
        }
};

int main() {
    return 0;
}