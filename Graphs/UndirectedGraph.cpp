#include <iostream>
#include <forward_list>
using namespace std;

class UndirectedGraph {
    private:
        int vertices;
        forward_list<int>* arr;
    public:
        UndirectedGraph(int vertices) {
            this->vertices = vertices;
            arr = new forward_list<int>[vertices];
        }

        void insertEdge(int v1, int v2) {
            if (v1 < vertices && v2 < vertices) {
                arr[v1].emplace_front(v2);
                arr[v2].emplace_front(v1);
            }
        }

        void display() {
            cout << "Adjacency List of Undirected Graph : " << endl;
            for(int i = 0; i < vertices; i++) {
                cout << "|" << i << "| : ";
                for(auto it: arr[i]) {
                    cout << "[" << it << "] -> ";
                }
                cout << "null" << endl;
            }
        }
};

enum {
    Delhi,
    Mumbai,
    Kolkata,
    Banglore,
    Kashmir
};

int main() {

    UndirectedGraph g(4);
    g.insertEdge(Delhi, Mumbai);
    g.insertEdge(Banglore, Mumbai);
    g.insertEdge(Kolkata, Delhi);
    g.display();

    return 0;
}