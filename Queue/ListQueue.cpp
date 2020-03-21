#include <iostream>
#include <list>
using namespace std;

template<typename T>
class Queue {
    private:
        list<T> ilist;
    
    public:
        Queue() {}

        void push(const T &data) {
            ilist.emplace_back(data);
        }

        void pop() {
            ilist.pop_front();
        }

        T front() {
           return ilist.front();
        }

        T back() {
           return ilist.back();
        }

        int size() {
            return ilist.size();
        }

        bool empty() {
            return ilist.empty();
        }

};

int main () {

    Queue<int> a;

    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);

    int size = a.size();
    for(int i = 0; i < size; i++) {
        cout << a.front() << " ";
        a.pop();
    }

    return 0;
}