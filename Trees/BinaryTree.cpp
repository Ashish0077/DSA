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

        static void preOrderTraversalRecursive(Node* root) {
            if(root != nullptr) {
                cout << root->getData() << " ";
                preOrderTraversalRecursive(root->getLeft());
                preOrderTraversalRecursive(root->getRight());
            }
        }

        static void inOrderTraversalRecursive(Node* root) {
            if(root != nullptr) {
                inOrderTraversalRecursive(root->getLeft());
                cout << root->getData() << " ";
                inOrderTraversalRecursive(root->getRight());
            }
        }

        static void postOrderTraversalRecursive(Node* root) {
            if(root != nullptr) {
                postOrderTraversalRecursive(root->getLeft());
                postOrderTraversalRecursive(root->getRight());
                cout << root->getData() << " ";
            }
        }

        static int getHeight(Node* root) {
            if(root == nullptr)
                return -1;
            return max(getHeight(root->getLeft()), getHeight(root->getRight())) + 1;
        }

        static void levelOrderTraversalRecursive(Node* root) {
            int h = getHeight(root);
            for(int i = 0; i <= h; i++)
                printLevel(root, i);
        }

        static void printLevel(Node* root, int level) {
            if(root == nullptr)
                return;
            if(level == 0)
                cout << root->getData() << " ";
            else if (level > 0) {
                printLevel(root->getLeft(), level - 1);
                printLevel(root->getRight(), level - 1);
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

    cout << "Height of the Tree : " << BinaryTree<int>::getHeight(root) << endl;

    // Depth First Search
    cout << "InOrder Recursive\n";
    BinaryTree<int>::inOrderTraversalRecursive(root);
    cout << "\nPostOrder Recursive\n";
    BinaryTree<int>::postOrderTraversalRecursive(root);
    cout << "\nPreOrder Recursive\n";
    BinaryTree<int>::preOrderTraversalRecursive(root);

    // Breadth First Search
    cout << "\nLevelOrder Recursive\n";
    BinaryTree<int>::levelOrderTraversalRecursive(root);
    cout << "\n";
    
    return 0;
}