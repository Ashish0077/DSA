#include <iostream>
using namespace std;

template<typename T>
class SinglyList {
    private:
        // node defination
        struct Node {
            T data;
            Node* next;
        };

        // internal head node
        Node* head;
        Node* tail;
        int _size;

        Node* createNewNode() {
            Node* node = new Node;
            node->next = NULL;
            return node;
        }

    public:
        SinglyList() {
            head = NULL;
            tail = head;
            _size = 0;
        }

        class Iterator {
            private:
                Node* it;
            public:
                Iterator(Node* it) {
                    this->it = it;
                }

                Node* &operator*() {
                    return it;
                }

                Iterator &operator++() {
                    it = it->next;
                    return *this;
                }

                Iterator &operator++(int k) {
                    it = it->next;
                    return *this;
                }

                bool operator!=(const Iterator &other) const{
                    return it != other.it;
                }

                bool operator==(const Iterator &other) const{
                    return it == other.it;
                }
        };

        Iterator begin() {
            return Iterator(head);
        }

        Iterator end() {
            return Iterator(NULL);
        }


        void emplaceBack(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            if(_size == 0) {
                head = newNode;
                tail = head;
            }
            tail->next = newNode;
            tail = newNode;
            _size++;
        }

        void emplaceFront(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            newNode->next = head;
            head = newNode;
            _size++;
        }



        void popBack() {
            Node* it = head;
            while (it->next != tail) {
                it = it->next;
            }

            it->next = NULL;
            delete tail;
            tail = it;
        }
 };

int main() {

    SinglyList<int> a;

    a.emplaceBack(1);
    a.emplaceBack(2);
    a.emplaceBack(3);
    a.emplaceBack(4);
    a.emplaceBack(5);

    for(auto i = a.begin(); i != a.end(); i++) {
        cout << (*i)->data << " -> ";
    }

    cout << endl;
    a.popBack();
    a.popBack();
    a.popBack();
    a.popBack();

    for(auto i : a) {
        cout << i->data << " -> ";
    }

    return 0;
}