#include <iostream>
#include <stack>

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

        static void preOrderTraversal(Node* root) {
            if(root == nullptr)
                return;
            
            stack<Node*> nodes;
            nodes.push(root);

            while(!nodes.empty()) {
                Node* current = nodes.top();
                nodes.pop();
                cout << current->getData() << " ";
                if(current->getLeft() != nullptr) nodes.push(current->getRight());
                if(current->getRight() != nullptr) nodes.push(current->getLeft());
            }
        }

        static void inOrderTraversalRecursive(Node* root) {
            if(root != nullptr) {
                inOrderTraversalRecursive(root->getLeft());
                cout << root->getData() << " ";
                inOrderTraversalRecursive(root->getRight());
            }
        }

        static void inOrderTraversal(Node* root) {
            stack<Node*> nodes;
            while(root != nullptr || !nodes.empty()) {
                
                // Pushing all the left nodes onto the stack
                while(root != nullptr) {
                    nodes.push(root);
                    root = root->getLeft();
                }

                // as the root will be null now
                root = nodes.top();
                nodes.pop();
                cout << root->getData() << " ";
                
                root = root->getRight();
            }
        }

        static void postOrderTraversalRecursive(Node* root) {
            if(root != nullptr) {
                postOrderTraversalRecursive(root->getLeft());
                postOrderTraversalRecursive(root->getRight());
                cout << root->getData() << " ";
            }
        }

        static void postOrderTraversal(Node* root) {
            stack<Node*> nodes;
            while(!nodes.empty() || root != nullptr) {
                
                // pushing all the left nodes on the stack
                while(root != nullptr) {
                    if(root->getRight() != nullptr) nodes.push(root->getRight());
                    nodes.push(root);
                    root = root->getLeft();
                }

                //currently root is null
                root = nodes.top();
                nodes.pop();

                if(nodes.empty()) {
                    cout << root->getData() << " ";
                    break;
                }

                if(root->getRight() != nullptr && nodes.top() == root->getRight()) {
                    nodes.pop(); // popped right node form the stack
                    nodes.push(root); // pushed root back
                    root = root->getRight(); // changed root to right so that right child is processed first
                } else {
                    cout << root->getData() << " ";
                    root = nullptr;
                }
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

    // constructing a tree
    /*  
                        1
                2               3     
            4      5        6       7
          8  9  10  11   13  14  15  16
    */
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
    cout << "\nInOrder Recursive\n";
    BinaryTree<int>::inOrderTraversalRecursive(root);
    cout << "\nInOrder Iterative\n";
    BinaryTree<int>::inOrderTraversal(root);
    cout << "\n\nPostOrder Recursive\n";
    BinaryTree<int>::postOrderTraversalRecursive(root);
    cout << "\nPostOrder Iterative\n";
    BinaryTree<int>::postOrderTraversal(root);
    cout << "\n\nPreOrder Recursive\n";
    BinaryTree<int>::preOrderTraversalRecursive(root);
    cout <<"\nPreOrder Iterative\n";
    BinaryTree<int>::preOrderTraversal(root);

    // Breadth First Search
    cout << "\n\nLevelOrder Recursive\n";
    BinaryTree<int>::levelOrderTraversalRecursive(root);
    cout << "\n";
    
    return 0;
}