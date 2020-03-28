#include <iostream>
#include <forward_list>
using namespace std;

class DirectedGraph {
    private:
        int vertices;
        forward_list<int>* arr;
    public:
        DirectedGraph(int v) {
            vertices = v;
            arr = new forward_list<int>[vertices];
        }

        void insertEdge(int source, int destination) {
            if (source < vertices && destination < vertices) {
                arr[source].emplace_front(destination);
            }
        }

        void display() {
            cout << "Adjacency List of Directed Graph : " << endl;
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
    DirectedGraph g(4);
    g.insertEdge(Delhi, Mumbai);
    g.insertEdge(Delhi, Banglore);
    g.insertEdge(Mumbai, Banglore);
    g.insertEdge(Banglore, Mumbai);
    g.insertEdge(Banglore, Kolkata);
    g.insertEdge(Kolkata, Mumbai);
    cout << endl;
    g.display();
    return 0;
}