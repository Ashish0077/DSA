#include <iostream>
#include <stack>
using namespace std;

template<typename T>
class BinarySearchTree {
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
        };

        // Recursive Node Insert function
        Node* add(Node* node, T data) {
            if(node == nullptr) {
                Node* n = new Node;
                n->data = data;
                n->left = nullptr;
                n->right = nullptr;

                return n;
            }

            if(data > node->data) {
                node->right = add(node->right, data);
            } else if (data < node->data) {
                node->left = add(node->left, data);
            }

            return node;
        }

        void inOrderTraversalRecursive(Node* node) {
            if (node != nullptr) {
                inOrderTraversalRecursive(node->left);
                cout << node->data << " ";
                inOrderTraversalRecursive(node->right);
            }
        }

        void preOrderTraversalRecursive(Node* node) {
            if (node != nullptr) {
                cout << node->data << " ";
                preOrderTraversalRecursive(node->left);
                preOrderTraversalRecursive(node->right);
            }
        }

        void postOrderTraversalRecursive(Node* node) {
            if (node != nullptr) {
                postOrderTraversalRecursive(node->left);
                postOrderTraversalRecursive(node->right);
                cout << node->data << " ";
            }
        }

        // Recursive Search function
        Node* search(Node* node, T data) {
            if(node == nullptr) {
                return nullptr;
            }

            if (node->data == data) {
                return node;
            } else if (node->data > data) {
                node = search(node->left, data);
            } else {
                node = search(node->right, data);
            }

            return node;
        } 

        Node* getMinNode(Node* node) {
            Node* current = node;
            while(current->left != nullptr) {
                current = current->left;
            }

            return current;
        }

        // recursive delete function
        Node* del(Node* node, T data) {
            if (node == nullptr) {
                return node;
            }

            if (data < node->data) {
                node->left = del(node->left, data);
            } else if (data > node->data) {
                node->right = del(node->right, data);
            } else {
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    free(node);
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    free(node);
                    return temp;
                }

                Node* temp = getMinNode(node->right);

                node->data = temp->data;
                node->right = del(node->right, temp->data);
            }

            return node;
        }

        Node* root;
    public:
        BinarySearchTree() {
            root = nullptr;
        }

        BinarySearchTree(T data) {
            root = new Node;
            root->data = data;
            root->left = nullptr;
            root->right = nullptr;
        }

        void insertRecursive(T data) {
            root = add(root, data);
        }

        int height(Node* current) {
            if (current == nullptr)
                return -1;
            
            return max(height(current->left), height(current->right)) + 1;
        }

        void insert(T data) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if(empty()) {
                root = newNode;
                return;
            }

            Node* current = root;
            Node* temp = nullptr;
            while(current != nullptr) {
                temp = current;
                if(data <= current->data)
                    current = current->left;
                else if (data > current->data)
                    current = current->right;
            }

            if(data <= temp->data) {
                temp->left = newNode;
            } else {
                temp->right = newNode;
            }
        }

        void removeRecursive(T data) {
            root = del(root, data);
        }

        void remove(T data) {
            Node* current = root;

            Node* p;
            while(current != nullptr) {
                if(data < current->data) {
                    p = current;
                    current = current->left;
                } else if (data > current->data) {
                    p = current;
                    current = current->right;
                } else {
                    if(current->left == nullptr && current->right == nullptr) {
                        if(current != root) {
                            if(p->left == current) {
                                p->left = nullptr;
                            } else if (p->right == current) {
                                p->right = nullptr;
                            }
                        } else {
                            root = nullptr;
                        }
                        delete current;
                    } else if (current->left != nullptr && current->right != nullptr) {
                        // find parent of inorder successor
                        Node* minP = nullptr;
                        Node* temp = current->right;
                        while(temp->left != nullptr) {
                            minP = temp;
                            temp = temp->left;
                        }
                        Node* min = (minP == nullptr) ? current->left : minP->left;

                        current->data = min->data;                        
                        if(minP == nullptr) {
                            current->left = nullptr;
                        } else {
                            minP->left = nullptr;
                        }
                        
                        delete min;
                    } else {
                        Node* child = current->left ? current->left : current->right;
                        if(current != root) {
                            if(p->left == current)
                                p->left = child;
                            else 
                                p->right = child;
                        } else {
                            root = child;
                        }
                        delete current;
                    }
                }
            }
        }

        Node* findRecursive(T data) {
            return search(root, data);
        }

        Node* find(T data) {
            Node* current = root;
            
            while(current != nullptr) {
                if(data < current->data)
                    current = current->left;
                else if (data > current->data)
                    current = current->right;
                else
                    return current;
            }

            return nullptr;
        }
        
        bool empty() {
            return root == nullptr;
        }

        int height() {
            return height(root);
        }

        void printInOrderRecursive() {
            inOrderTraversalRecursive(root);
        }

        void printInOrderIterative() {
            stack<Node*> nodes;
            Node* current = root;
            while(current != nullptr || !nodes.empty()) {

                while(current != nullptr) {
                    nodes.push(current);
                    current = current->left;
                }

                // currently root is null
                current = nodes.top();
                nodes.pop();
                cout << current->data << " ";
                current = current->right;
            }
        }

        void printPreOrderRecursive() {
            preOrderTraversalRecursive(root);
        }

        void printPreOrderIterative() {
            stack<Node*> nodes;
            Node* current = root;
            nodes.push(current);
            while(!nodes.empty()) {
                current = nodes.top();
                nodes.pop();
                cout << current->data << " ";
                if(current->right != nullptr) nodes.push(current->right);
                if(current->left != nullptr) nodes.push(current->left);
            }
        }

        void printPostOrderRecursive() {
            postOrderTraversalRecursive(root);
        }

        void printPostOrderIterative() {
            stack<Node*> nodes;
            Node* current = root;
            while(current != nullptr || !nodes.empty()) {

                while(current != nullptr) {
                    if(current->right != nullptr) nodes.push(current->right);
                    nodes.push(current);
                    current = current->left;
                }

                current = nodes.top();
                nodes.pop();

                if(nodes.empty()) {
                    cout << current->data << " ";
                    break;
                }

                if(current->right != nullptr && nodes.top() == current->right) {
                    nodes.pop();
                    nodes.push(current);
                    current = current->right;
                } else {
                    cout << current->data << " ";
                    current = nullptr;
                }
            }
        }
};

int main() {

    BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insertRecursive(30);
    tree.insert(20);
    tree.insertRecursive(40);
    tree.insert(70);
    tree.insertRecursive(60);
    tree.insert(80);
    tree.insertRecursive(75);
    tree.insert(35);
    cout << "Height Of the Tree : " << tree.height() << endl;
    
    cout << "\nPostOrder Traversal Recursive\n"; 
    tree.printPostOrderRecursive();
    cout << "\nPostOrder Traversal Iterative\n";
    tree.printPostOrderIterative();
    cout << "\n\nPreOrder Traversal Recursive\n"; 
    tree.printPreOrderRecursive();
    cout << "\nPreOrder Traversal Iterative\n";
    tree.printPreOrderIterative();
    cout << "\n\nInOrder Traversal Recursive\n"; 
    tree.printInOrderRecursive();
    cout << "\nInOrder Traversal Iterative\n";
    tree.printInOrderIterative();

    cout << "\n\nSearching for 70 iteratively\n";
    auto it = tree.find(70);
    if(it)
        cout << "Found\n";
    else 
        cout << "Not Found\n";
    cout << "Searching for 90 Recursively\n";
    auto it2 = tree.findRecursive(90);
    if(it2)
        cout << "Found\n";
    else 
        cout << "Not Found\n";
    
    cout << "\nDeleting 75 Iteratively\n";
    tree.remove(75);
    tree.printInOrderIterative();
    cout << endl;

    cout << "\nDeleting 70 Recursively\n";
    tree.remove(70);
    tree.printInOrderIterative();
    cout << endl;
    return 0;
}