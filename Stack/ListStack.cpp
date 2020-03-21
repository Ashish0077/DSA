#include<iostream>
#include<list>
using namespace std;

template<typename T>
class Stack {
    private:
        // internal linked list
        list<T> _top;
    public:
        Stack() {}

        /*
            This function is used to push elements
            to the top of the stack
            Time Complexity: O(1)
        */
        void push(const T &data) {
            _top.emplace_back(data);
        }

        /*  
            This function is used to pop the top
            element of the stack
            Time Complexity: O(1)
        */
        void pop() {
            _top.pop_back();
        }

        /*  
            This fucntion is used to return the
            top of the stack
            Time Complexity: o(1)
        */
        T top() {
            return _top.back();
        }

        /*  
            Returns if the stack is empty or not
        */
        bool empty() {
            return _top.empty();
        }
        
        /*
            This is used to return the size of stack
        */
        int size() {
           return _top.size();
        }
};


int main() {

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