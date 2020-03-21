#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Queue {
    private:
        vector<T> idarr;
    public:
        Queue() {
        }

        void push(const T &data) {
            idarr.emplace_back(data);
        }

        void pop() {
            idarr.erase(idarr.begin());
        }

        T front() {
           return idarr.front();
        }

        T back() {
           return idarr.back();
        }

        int size() {
            return idarr.size();
        }

        bool empty() {
            return idarr.empty();
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