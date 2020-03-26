#include <iostream>
using namespace std;

template<typename T>
class BinaryTree {
    public:
        class Node {
            private:
                Node* left;
                Node* right;
                T data;
            public:
                Node(T data) {
                    this->data = data;
                    left = nullptr;
                    right = nullptr;
                }

                Node* getLeft() const{
                    return left;
                }

                Node* getRight() const{
                    return right;
                }

                void setLeft(T data) {
                    left = new Node(data);
                }

                void setRight(T data) {
                    right = new Node(data);
                }

                T getData() const{
                    return data;
                }
        };

        static void preOrderTraversal(Node* root) {
            if(root != nullptr) {
                cout << root->getData() << " ";
                preOrderTraversal(root->getLeft());
                preOrderTraversal(root->getRight());
            }
        }

        static void inOrderTraversal(Node* root) {
            if(root != nullptr) {
                inOrderTraversal(root->getLeft());
                cout << root->getData() << " ";
                inOrderTraversal(root->getRight());
            }
        }

        static void postOrderTraversal(Node* root) {
            if(root != nullptr) {
                postOrderTraversal(root->getLeft());
                postOrderTraversal(root->getRight());
                cout << root->getData() << " ";
            }
        }

};

int main () {

    auto root = new BinaryTree<int>::Node(1);
    root->setLeft(2);
    root->setRight(3);
    root->getLeft()->setLeft(4);
    root->getLeft()->setRight(5);
    root->getRight()->setLeft(6);
    root->getRight()->setRight(7);
    root->getLeft()->getLeft()->setLeft(8);
    root->getLeft()->getLeft()->setRight(9);
    root->getLeft()->getRight()->setLeft(10);
    root->getLeft()->getRight()->setRight(11);
    root->getRight()->getLeft()->setLeft(12);
    root->getRight()->getLeft()->setRight(13);
    root->getRight()->getRight()->setLeft(14);
    root->getRight()->getRight()->setRight(15);

    BinaryTree<int>::inOrderTraversal(root);
    cout << endl;
    BinaryTree<int>::postOrderTraversal(root);
    cout << endl;
    BinaryTree<int>::preOrderTraversal(root);
    cout << endl;

    return 0;
}