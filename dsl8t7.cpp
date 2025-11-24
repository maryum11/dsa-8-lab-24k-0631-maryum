//median of bst
include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v): data(v), left(nullptr), right(nullptr) {}
};

int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Kth smallest without vector
int kthSmallest(Node* root, int k) {
    Node* stack[100];
    int top = -1;
    Node* curr = root;
    int count = 0;

    while (curr || top != -1) {
        while (curr) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        count++;
        if (count == k) return curr->data;
        curr = curr->right;
    }
    return -1;
}

double findMedian(Node* root) {
    int n = countNodes(root);
    if (n % 2 == 1) return kthSmallest(root, (n+1)/2);
    else return (kthSmallest(root, n/2) + kthSmallest(root, n/2+1)) / 2.0;
}

int main() {
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);

    cout << "Median: " << findMedian(root);
    return 0;
}
