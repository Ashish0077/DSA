#include <iostream>
using namespace std;

template<typename T>
class DoublyList {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;
        };

        Node* head;
        Node* tail;
        int _size;

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

        class ForwardIterator {
            private:
                Node* it;

            public:
                ForwardIterator(Node* h) {
                    it = h;
                }

                Node* &operator*() {
                    return it; 
                }

                ForwardIterator &operator++() {
                    it = it->next;
                    return *this;
                }

                ForwardIterator &operator--() {
                    it = it->prev;
                    return *this;
                }

                ForwardIterator &operator++(int k) {
                    it = it->next;
                    return *this;
                }

                ForwardIterator &operator--(int k) {
                    it = it->prev;
                    return *this;
                }

                ForwardIterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                ForwardIterator &operator-(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->prev;
                    }
                    return *this;
                }

                bool operator!=(const ForwardIterator &other) {
                    return it != other.it;
                }

                bool operator==(const ForwardIterator &other) {
                    return it == other.it;
                }
        };

        ForwardIterator begin() {
            return  ForwardIterator(head);
        }

        ForwardIterator end() {
            return  ForwardIterator(NULL);
        }

        class BackwardIterator {
            private:
                Node* it;

            public:
                BackwardIterator(Node* t) {
                    it = t;
                }

                Node* &operator*() {
                    return it; 
                }

                BackwardIterator &operator++() {
                    it = it->prev;
                    return *this;
                }

                BackwardIterator &operator--() {
                    it = it->next;
                    return *this;
                }

                BackwardIterator &operator++(int k) {
                    it = it->prev;
                    return *this;
                }

                BackwardIterator &operator--(int k) {
                    it = it->next;
                    return *this;
                }

                BackwardIterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->prev;
                    }
                    return *this;
                }

                BackwardIterator &operator-(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                bool operator!=(const BackwardIterator &other) {
                    return it != other.it;
                }

                bool operator==(const BackwardIterator &other) {
                    return it == other.it;
                }
        };

        BackwardIterator rBegin() {
            return BackwardIterator(tail);
        }

        BackwardIterator rEnd() {
            return BackwardIterator(NULL);
        }

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

        int size() {
            return _size;
        }

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