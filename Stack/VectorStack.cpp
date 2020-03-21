#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Stack {
    private:
        vector<T> _top;
    
    public:
        Stack() {}

        void push(const T &data) {
            _top.emplace_back(data);
        }

        void pop() {
            _top.pop_back();
        }

        T top() {
            return _top.back();
        }

        bool empty() {
            return _top.empty();
        }

        int size() {
            return _top.size();
        }
};

int main () {

    // test code
    Stack<int> a;

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