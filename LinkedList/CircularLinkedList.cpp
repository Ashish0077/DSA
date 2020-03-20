#include <iostream>
#include <string>
using namespace std;

template<typename T>
class CircularList {
    private:
        /*
            structure of node, containing a self referential pointers
            to maintian next node's link
        */
        struct Node {
            T data;
            Node* next;
        };

        // internal head node
        Node* head;
        // internal tail node
        Node* tail;
        // this keeps track of number of nodes in the list
        int _size;

        /*
            This function is used to create new empty nodes
        */
        Node* createNewNode() {
            Node* node = new Node;
            node->next = head;
            return node;
        }

    public:
        CircularList() {
            head = NULL;
            tail = head;
            _size = 0;
        }

        /*
            Iterator Class:
            All functinality for iterating the list in forward direction and in circular manner
        */
        class Iterator {
            private:
                Node* it;
                Node* h; // this is to keep track when list ends
            public:
                Iterator(Node* it) {
                    this->it = it;
                    if(it != NULL) {
                        h = it;
                    }
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
                    if the next is equals to head it sets the internal node to NULL (this makes the for-each loop functionality work)
                */
                Iterator &operator++() {
                    it = it->next;
                    if(it == h) {
                        it = NULL;
                    }
                    return *this;
                }

                 /*
                    Overloading prefix ++ operator
                    this makes the iterator to move to next node
                    if the next is equals to head it sets the internal node to NULL (this makes the for-each loop functionality work)
                */
                Iterator &operator++(int k) {
                    it = it->next;
                    if(it == h) {
                        it = NULL;
                    }
                    return *this;
                }

                /*
                    Overloading + operator this helps to traverse 
                    to nth node
                    this can be used to do circular traversal on the list
                */
                Iterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                bool operator!=(const Iterator &other) const{
                    return it != other.it;
                }

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
            from the ending of the list (NULL)
            begin() and end() helps in implementing for-each loop
        */
        Iterator end() {
            return Iterator(NULL);
        }

        /*
            This function is used to insert elements
            at the back/end of the list
            Time Complexity : O(1)
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
            tail->next = head;
            _size++;
        }

        /*
            This function is used to delete elements
            from the back of the list
            Time Complexity : O(n-1)
            it traverses to the previous node to the tail
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

            it->next = head;
            delete tail;
            tail = it;
        }

        /*
            This function is used to delete elements
            from the front of the list
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
            tail->next = head;
        }

        /*
            This function is used to insert element at nth
            position from the head
            Time Complexity : O(n)
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
                it = it++;
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
            while(head != tail) {
                Node* del = head;
                head = head->next;
                del->next = NULL;
                delete del;
                tail->next = head;
            }
            head = NULL;
            tail = head;
            _size = 0;
        }
 };

int main() {

    CircularList<string> a;

    cout << "Size : " << a.size() << endl;

    a.emplaceBack("Mango");
    a.emplaceBack("Apple");
    a.emplaceBack("Guava");

    // 0 indexed
    a.insert(a.begin() , "Banana");

    // For circularly iterating the list
    auto check = a.begin();
    for(int i = 0; i < 9; i++) {
        check = check + 1; // do not use ++ operator for circular iteration
    }
    cout << (*check)->data << endl;


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