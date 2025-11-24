#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v): data(v), left(nullptr), right(nullptr) {}
};

int countNodesInRange(Node* root, int a, int b) {
    if (!root) return 0;

    if (root->data >= a && root->data <= b)
        return 1 + countNodesInRange(root->left, a, b)
                 + countNodesInRange(root->right, a, b);

    else if (root->data < a)
        return countNodesInRange(root->right, a, b);

    else
        return countNodesInRange(root->left, a, b);
}

int main() {
    Node* root = new Node(20);
    root->left = new Node(10);
    root->right = new Node(40);
    root->left->left = new Node(5);

    int a = 5, b = 45;

    cout << "Nodes in range: " << countNodesInRange(root, a, b);

    return 0;
}
