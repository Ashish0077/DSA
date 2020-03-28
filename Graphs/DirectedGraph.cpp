#include <iostream>
#include <forward_list>
using namespace std;

template<typename T>
class DirectedGraph {
    private:
        int vertices;
        forward_list<pair<int, T>>* arr;
    public:
        DirectedGraph(int v) {
            vertices = v;
            arr = new forward_list<pair<int, T>>[vertices];
        }

        void insertEdge(int source, int destination, T data) {
            if (source < vertices && destination < vertices) {
                arr[source].emplace_front(destination, data);
            }
        }

        void display() {
            cout << "Adjacency List of Directed Graph : " << endl;
            for(int i = 0; i < vertices; i++) {
                cout << "|" << i << "| : ";
                for(auto it: arr[i]) {
                    cout << "[" << it.first << ", " << it.second << "] -> ";
                }
                cout << "null" << endl;
            }
        }
};

int main() {
    DirectedGraph<string> g(4);
    g.insertEdge(0, 1, "Delhi");
    g.insertEdge(0, 2, "Noida");
    g.insertEdge(1, 3, "Gurgaon");
    g.insertEdge(2, 3, "Ghaziabad");
    cout << endl;
    g.display();
    return 0;
}