#include <iostream>
using namespace std;

template<typename T>
class BinarySearchTree {
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
        };

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

        void inOrderTraversal(Node* node) {
            if (node != nullptr) {
                inOrderTraversal(node->left);
                cout << node->data << " ";
                inOrderTraversal(node->right);
            }
        }

        void preOrderTraversal(Node* node) {
            if (node != nullptr) {
                cout << node->data << " ";
                preOrderTraversal(node->left);
                preOrderTraversal(node->right);
            }
        }

        void postOrderTraversal(Node* node) {
            if (node != nullptr) {
                postOrderTraversal(node->left);
                postOrderTraversal(node->right);
                cout << node->data << " ";
            }
        }

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

        Node* del(Node* node, T data) {
            if (node == nullptr) {
                return node;
            }

            if (data < node->data) {
                node->left = del(node->left, data);
            } else if (data > node->data) {
                node->right = del(node->right, data);
            } else {
                if (node->left = nullptr) {
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

        void insert(T data) {
            root = add(root, data);
        }

        void remove(T data) {
            root = del(root, data);
        }

        Node* find(T data) {
            return search(root, data);
        }

        bool empty() {
            return root == nullptr;
        }

        void printInOrder() {
            inOrderTraversal(root);
        }
        void printPreOrder() {
            preOrderTraversal(root);
        }
        void printPostOrder() {
            postOrderTraversal(root);
        }
};

int main() {

    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);

    tree.printPostOrder();

    auto it = tree.find(7);
    if(it == nullptr) {
        cout << "Not Found" << endl;
    } else {
        cout << "found : " << it->data << endl;
    }
    cout << endl;
    tree.remove(7);
    tree.printPostOrder();

    return 0;
}