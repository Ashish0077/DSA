#include <iostream>
using namespace std;

template<typename T>
class DoublyList {
    private:
        /*
            structure of node, containing two self referential pointers
            to maintian next and prev links
        */
        struct Node {
            T data;
            Node* next;
            Node* prev;
        };

        // starting node of the list
        Node* head;
        // ending node of the list
        Node* tail;
        // this keeps track of the number of nodes in the list
        int _size;

        /*
            This function is used to create new empty nodes
        */
        Node* createNewNode() {
            Node* node = new Node;
            node->prev = NULL;
            node->next = NULL;
            return node;
        }
    
    public:
        DoublyList() {
            head = NULL;
            tail = NULL;
            _size = 0;
        }
        /*
            ForwardIterator Class:
            All functinality for iterating the list in forward direction
        */
        class ForwardIterator {
            private:
                Node* it;

            public:
                ForwardIterator(Node* h) {
                    it = h;
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
                ForwardIterator &operator++() {
                    it = it->next;
                    return *this;
                }

                /*
                    Overloading prefix -- operator
                    this makes the iterator to move to previous node
                */
                ForwardIterator &operator--() {
                    it = it->prev;
                    return *this;
                }

                /*
                    Overloading postfix ++ operator
                    this makes the iterator to move to next node
                */
                ForwardIterator &operator++(int k) {
                    it = it->next;
                    return *this;
                }

                /*
                    Overloading postfix -- operator
                    this makes the iterator to move to previous node
                */
                ForwardIterator &operator--(int k) {
                    it = it->prev;
                    return *this;
                }

                /*
                    Overloading + operator this helps to traverse 
                    to nth node
                */
                ForwardIterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                /*
                    Overloading - operator this helps to traverse to nth node 
                */
                ForwardIterator &operator-(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->prev;
                    }
                    return *this;
                }
                
                /*
                    Overloading != operator
                    this is used for comparision
                    returns true when not equal else false
                */
                bool operator!=(const ForwardIterator &other) {
                    return it != other.it;
                }

                /*
                    Overlaading == operator
                    this is used for comparision
                    return true when equal else false
                */
                bool operator==(const ForwardIterator &other) {
                    return it == other.it;
                }
        };

        
        /*
            This function is used to get a ForwardIterator
            from the begining of the list
            begin() and end() helps in implementing for-each loop
        */
        ForwardIterator begin() {
            return  ForwardIterator(head);
        }

        /*
            This function is used to get a ForwardIterator
            from the ending of the list
            begin() and end() helps in implementing for-each loop
        */
        ForwardIterator end() {
            return  ForwardIterator(NULL);
        }
        
        /*
            Backwardterator Class:
            All functinality for iterating the list in backward direction
        */
        class BackwardIterator {
            private:
                Node* it;

            public:
                BackwardIterator(Node* t) {
                    it = t;
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
                BackwardIterator &operator++() {
                    it = it->prev;
                    return *this;
                }

                /*
                    Overloading prefix -- operator
                    this makes the iterator to move to previous node
                */
                BackwardIterator &operator--() {
                    it = it->next;
                    return *this;
                }
                
                /*
                    Overloading postfix ++ operator
                    this makes the iterator to move to next node
                */
                BackwardIterator &operator++(int k) {
                    it = it->prev;
                    return *this;
                }

                /*
                    Overloading postfix -- operator
                    this makes the iterator to move to previous node
                */
                BackwardIterator &operator--(int k) {
                    it = it->next;
                    return *this;
                }

                /*
                    Overloading + operator this helps to traverse 
                    to nth node
                */
                BackwardIterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->prev;
                    }
                    return *this;
                }

                /*
                    Overloading - operator this helps to traverse to nth node 
                */
                BackwardIterator &operator-(int k) {
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
                bool operator!=(const BackwardIterator &other) {
                    return it != other.it;
                }

                /*
                    Overlaading == operator
                    this is used for comparision
                    return true when equal else false
                */
                bool operator==(const BackwardIterator &other) {
                    return it == other.it;
                }
        };

        /*
            This function is used to get a BackwardIterator
            from the begining of the list
        */
        BackwardIterator rBegin() {
            return BackwardIterator(tail);
        }

        /*
            This function is used to get a BackwardIterator
            from the ending of the list
        */
        BackwardIterator rEnd() {
            return BackwardIterator(NULL);
        }

        /*
            This function is used to insert elements
            at the back/end of the list
            Time Complexity : O(1)
        */
        void emplaceBack(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            if (_size == 0) {
                head = newNode;
                tail = head;
                _size++;
                return;
            }
            newNode->prev = tail;
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
            if(_size == 0) {
                head = newNode;
                tail = head;
                _size++;
                return;
            }
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            _size++;
        }

        /*
            This function is used to delete elements
            at from the back of the list
            Time Complexity : O(1)
        */
        void popBack() {
            _size--;
            if(_size <= 0) {
                delete head;
                head = NULL;
                tail = NULL;
                _size = 0;
                return;
            }
            Node* del = tail;
            tail = tail->prev;
            tail->next = NULL;
            del->prev = NULL;
            delete del;
        }

        /*
            This function is used to delete elements
            at from the back of the list
            Time Complexity : O(1)
        */
        void popFront() {
            _size--;
            if(_size <= 0) {
                delete head;
                head = NULL;
                tail = NULL;
                _size = 0;
                return;
            }
            Node* del = head; 
            head = head->next;
            head->prev = NULL;
            del->next = NULL;
            delete del;
        }

        /*
            This function is used to insert element at nth
            position from the head
            Time Complexity : O(1) (it does not traverse the list)
            (the input is already having the node)
        */
        void insert(ForwardIterator at,const T &data) {
            if (begin() == at) {
                emplaceFront(data);
                return;
            } else if (end() == at) {
                emplaceBack(data);
                return;
            }

            Node* newNode = createNewNode();
            newNode->data = data;
            newNode->next = (*at);
            newNode->prev = (*at)->prev;
            (*at)->prev = newNode;
            (newNode->prev)->next = newNode;
            _size++;
        }

        /*
            This function is used to insert element at nth
            position from the tail
            Time Complexity : O(1) (it does not traverse the list)
            (the input is already having the node)
        */
        void insert(BackwardIterator at, const T &data) {
            if (rBegin() == at) {
                emplaceBack(data);
                return;
            } else if(rEnd() == at) {
                emplaceFront(data);
                return;
            }

            Node* newNode = createNewNode();
            newNode->data = data;
            newNode->prev = (*at);
            newNode->next = (*at)->next;
            (*at)->next = newNode;
            (newNode->next)->prev = newNode;
            _size++;

        }

        /*  
            this just returns the size of the list
            (no. of nodes)
        */
        int size() {
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

int main () {

    // test code
    DoublyList<string> a;

    a.emplaceFront("mango");
    a.emplaceFront("apple");
    a.emplaceBack("guava");

    a.emplaceBack("Blue");
    a.emplaceBack("Green");
    a.emplaceBack("Yellow");

    a.insert(a.begin() + 4, "Purple");
    a.insert(a.rBegin() + 2, "Mustard");

    for(auto it = a.rBegin(); it != a.rEnd(); it++) {
        cout << (*it)->data << " <-> ";
    }
    cout << endl;
    
    for (auto it: a) {
        cout << it->data << " <-> ";
    }
    cout << endl;
    
    a.popBack();
    a.popBack();
    a.popBack();

    return 0;
}