#include <iostream>
#include <algorithm>
#include <array>
using namespace std;

template<typename T, int k>
class Queue {
    private:
        array<T, k> iarr;
        int _back;
    public:
        Queue() {
            _back = -1;
        }

        void push(const T &data) {
            _back++;
            if (size() <= k) {
                iarr[_back] = data;
            } else {
                throw overflow_error("QUEUE FULL");
            }
        }

        void pop() {
            if(size() > 0) {
                rotate(iarr.begin(), iarr.begin() + 1, iarr.end());
                _back--;
            } else {
                throw underflow_error("QUEUE EMPTY");
            }
        }

        T front() {
           return *(iarr.begin());
        }

        T back() {
           return *(iarr.begin() + k);
        }

        int size() {
            return _back + 1;
        }

        bool empty() {
            return _back == -1;
        }

};

int main () {

    Queue<int, 5> a;

    a.push(1);
    a.pop();
    a.push(2);    
    a.push(3);    
    a.pop();    
    a.push(4);    
    a.push(5);
    a.pop();
    a.push(1);

    int size = a.size();
    for(int i = 0; i < size; i++) {
        cout << a.front() << " ";
        a.pop();
    }

    return 0;
}