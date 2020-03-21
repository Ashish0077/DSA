#include <iostream>
#include <array>
using namespace std;

template<typename T, int k>
class Stack {
    private:
        array<T, k> arr;
        int i;
    public:
        Stack() {
            i = -1;
        }

        void push(const T &data) {
            if (i < k) {
                i++;
                arr[i] = data;
            } else {
                throw overflow_error("Stack Overflow");
            }
        }

        void pop() {
            if (i >= 0) {
                arr[i] = 0;
                i--;
            } else {
                throw underflow_error("Stack Underflow");
            }
        }

        T top() {
            return arr[i];
        }

        bool empty() {
            return arr.empty();
        }

        int size() {
            return i + 1;
        }

};

int main() {

    Stack<int, 5> a;

    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);

    int size = a.size();
    for(int i = 0; i < size; i++) {
        cout << a.top() << " ";
        a.pop();
    }

    return 0;
}