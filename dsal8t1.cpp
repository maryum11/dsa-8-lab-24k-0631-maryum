#include <iostream>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};
class BinarySearchTree{
private:
    Node* root;
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }
    bool search(Node* node, int key) {
        if (node == nullptr)
            return false;
        if (node->data == key)
            return true;
        else if (key < node->data)
            return search(node->left, key);
        else
            return search(node->right, key);
    }
    void inorder(Node* node) {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void preorder(Node* node) {
        if (node == nullptr)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(Node* node) {
        if (node == nullptr)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }
    Node* deleteNode(Node* node, int key) {
        if (node == nullptr)
            return node;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }
    void insert(int value) {
        root = insert(root, value);
    }
    void deleteNode(int key) {
        root = deleteNode(root, key);
    }
    bool search(int key) {
        return search(root, key);
    }
    void inorder() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }
    void preorder() {
        cout << "Preorder Traversal: ";
        preorder(root);
        cout << endl;
    }
    void postorder() {
        cout << "Postorder Traversal: ";
        postorder(root);
        cout << endl;
    }
};
int main() {
    BinarySearchTree tree;
    int choice, value;

    while (true) {
        cout << "\nBinary Search Tree Operations:";
        cout << "\n1. Insert";
        cout << "\n2. Delete";
        cout << "\n3. Search";
        cout << "\n4. Inorder Traversal";
        cout << "\n5. Preorder Traversal";
        cout << "\n6. Postorder Traversal";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(value))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found.\n";
                break;
            case 4:
                tree.inorder();
                break;
            case 5:
                tree.preorder();
                break;
            case 6:
                tree.postorder();
                break;
            case 7:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
