#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SinglyList {
    private:
        /*
            structure of node, containing a self referential pointer
            to maintian the link to the next node
        */
        struct Node {
            T data;
            Node* next;
        };

        // starting node of the list
        Node* head;

        // ending node of the list (this is used to optimize the insertion operation)
        Node* tail;

        // this keeps track of the number of nodes in the list
        int _size;

        /*
            This function is used to create new empty nodes
        */
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

        /*
            Iterator Class:
            All functinality for iterating the list in forward direction
        */
        class Iterator {
            private:
                Node* it;
            public:
                Iterator(Node* it) {
                    this->it = it;
                }

                /*
                    Overloading * operator to make internal node accessible
                */
                Node* &operator*() {
                    return it;
                }

                /*
                    Overloading prefix ++ operator
                    this makes the iterator to move to next node
                */
                Iterator &operator++() {
                    it = it->next;
                    return *this;
                }
                
                /*
                    Overloading postfix ++ operator
                    this makes the iterator to move to next node
                */
                Iterator &operator++(int k) {
                    it = it->next;
                    return *this;
                }

                /*
                    Overloading + operator this helps to traverse 
                    to nth node
                */
                Iterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                /*
                    Overloading != operator
                    this is used for comparision
                    returns true when not equal else false
                */
                bool operator!=(const Iterator &other) const{
                    return it != other.it;
                }

                 /*
                    Overlaading == operator
                    this is used for comparision
                    return true when equal else false
                */
                bool operator==(const Iterator &other) const{
                    return it == other.it;
                }
        };

        /*
            This function is used to get a Iterator
            from the begining of the list
            begin() and end() helps in implementing for-each loop
        */
        Iterator begin() {
            return Iterator(head);
        }

        /*
            This function is used to get a Iterator
            from the ending of the list
            begin() and end() helps in implementing for-each loop
        */
        Iterator end() {
            return Iterator(NULL);
        }

        /*
            This function is used to insert elements
            at the back/end of the list
            Time Complexity : O(1) as the last node is tracked 
            but tail pointer
        */
        void emplaceBack(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            if(_size == 0) {
                head = newNode;
                tail = head;
                _size++;
                return;
            }
            tail->next = newNode;
            tail = newNode;
            _size++;
        }

        /*
            This function is used to insert elements
            at the start/front of the list
            Time Complexity : O(1)
        */
        void emplaceFront(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            if (_size == 0) {
                head = newNode;
                tail = head;
                _size++;
                return;
            }
            newNode->next = head;
            head = newNode;
            _size++;
        }

        /*
            This function is used to delete elements
            at from the back of the list
            Time Complexity : O(n) it traveres to
            previous node to the tail
        */
        void popBack() {
            _size--;
            if (_size <= 0) {
                delete head;
                head = NULL;
                tail = NULL;
                _size = 0;
                return;
            }
            Node* it = head;
            while (it->next != tail) {
                it = it->next;
            }

            it->next = NULL;
            delete tail;
            tail = it;
        }

        /*
            This function is used to delete elements
            at from the front of the list
            Time Complexity : O(1)
        */
        void popFront() {
             _size--;
            if (_size <= 0) {
                delete head;
                head = NULL;
                tail = NULL;
                _size = 0;
                return;
            }
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        /*
            This function is used to insert element at nth
            position from the head
            Time Complexity : O(n) it had to traverse to one previous
            node to the location to insert (it is due to the nature of
            od the list, it moves in forward direction only)
        */
        void insert(Iterator at,const T &data) {
            
            if (begin() == at) {
                emplaceFront(data);
                return;
            } else if(end() == at) {
                emplaceBack(data);
                return;
            }

            Node* newNode = createNewNode();
            newNode->data = data;
            auto it = begin();
            while((*it)->next != (*at)) {
                it++;
            }
            newNode->next = (*at);
            (*it)->next = newNode;
            _size++;
        }

        /*  
            this just returns the size of the list
            (no. of nodes)
        */
        int size() const {
            return _size;
        }

        /*
            This function is used to delete the whole list
            fromt the memory
        */
        void clear() {
            while(head != NULL) {
                Node* del = head;
                head = head->next;
                del->next = NULL;
                delete del;
            }
            head = NULL;
            tail = head;
            _size = 0;
        }
 };

int main() {

    SinglyList<string> a;

    cout << "Size : " << a.size() << endl;

    a.emplaceBack("Mango");
    a.emplaceBack("Apple");
    a.emplaceBack("Guava");
    a.clear();

    // 0 indexed
    a.insert(a.begin() , "Banana");

    // Method 1: iterating Linked List
    auto it = a.begin();
    for(int i = 0; i < a.size(); i++) {
        cout << (*it)->data << " -> ";
        (*it) = (*it)->next;
    }
    cout << "NULL\n";
    
    cout << "Size : " << a.size() << endl;

    a.emplaceBack("Pineapple");
    a.emplaceBack("Cherry");
    
    // Method 2: Iterating Linked List
    for(auto i = a.begin(); i != a.end(); i++) {
        cout << (*i)->data << " -> ";
    }
    cout << "NULL\n";

    a.emplaceFront("Orange");
    
    for(auto i = a.begin(); i != a.end(); i++) {
        cout << (*i)->data << " -> ";
    }
    cout << "NULL\n";

    cout << "Size : " << a.size() << endl;

    a.popBack();
    a.popBack();

    cout << "Size : " << a.size() << endl;
    
    // Method 3: Iterating Linked List
    for(auto i : a) {
        cout << i->data << " -> ";
    }
    cout << "NULL\n";

    a.popFront();
    a.popFront();
    
    cout << "Size : " << a.size() << endl;

    for(auto i : a) {
        cout << i->data << " -> ";
    }
    cout << "NULL\n";

    return 0;
}