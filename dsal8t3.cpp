#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   
using namespace std;
class Student {
public:
    string name;
    int roll;
    int score;
    Student() {}
    Student(string n, int r, int s) {
        name = n;
        roll = r;
        score = s;
    }
};
class Node {
public:
    Student data;
    Node* left;
    Node* right;

    Node(Student s) {
        data = s;
        left = right = nullptr;
    }
};
class BST {
private:
    Node* root;
    Node* insert(Node* root, Student s) {
        if (root == nullptr)
            return new Node(s);

        if (s.name < root->data.name)
            root->left = insert(root->left, s);
        else if (s.name > root->data.name)
            root->right = insert(root->right, s);
        return root;
    }
    Node* search(Node* root, string name) {
        if (root == nullptr || root->data.name == name)
            return root;
        if (name < root->data.name)
            return search(root->left, name);
        return search(root->right, name);
    }
    Node* deleteLowScores(Node* root) {
        if (root == nullptr)
            return nullptr;
        root->left = deleteLowScores(root->left);
        root->right = deleteLowScores(root->right);
        if (root->data.score < 10) {
            root = deleteNode(root, root->data.name);
        }
        return root;
    }
    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }
    Node* deleteNode(Node* root, string name) {
        if (root == nullptr)
            return root;
        if (name < root->data.name)
            root->left = deleteNode(root->left, name);
        else if (name > root->data.name)
            root->right = deleteNode(root->right, name);
        else {
            if (root->left == nullptr && root->right == nullptr)
                return nullptr;
            else if (root->left == nullptr)
                return root->right;
            else if (root->right == nullptr)
                return root->left;
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.name);
        }
        return root;
    }
    void findMaxScore(Node* root, Student &maxStudent) {
        if (root == nullptr)
            return;
        if (root->data.score > maxStudent.score)
            maxStudent = root->data;
        findMaxScore(root->left, maxStudent);
        findMaxScore(root->right, maxStudent);
    }
    void inorder(Node* root) {
        if (root == nullptr)
            return;
        inorder(root->left);
        cout << root->data.name << " (Roll: " << root->data.roll
             << ", Score: " << root->data.score << ")\n";
        inorder(root->right);
    }

public:
    BST() { root = nullptr; }

    void insert(Student s) { root = insert(root, s); }

    void search(string name) {
        Node* res = search(root, name);
        if (res)
            cout << "Found -> Name: " << res->data.name
                 << ", Roll: " << res->data.roll
                 << ", Score: " << res->data.score << "\n";
        else
            cout << "Student not found!\n";
    }

    void deleteLowScores() { root = deleteLowScores(root); }

    void display() {
        cout << "\n--- Students in BST (Inorder Traversal) ---\n";
        inorder(root);
    }
    void getMaxScore() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }
        Student maxStudent = root->data;
        findMaxScore(root, maxStudent);
        cout << "\nStudent with Max Score:\n";
        cout << "Name: " << maxStudent.name
             << ", Roll: " << maxStudent.roll
             << ", Score: " << maxStudent.score << "\n";
    }
};
int main() {
    srand(time(0));
    Student students[10] = {
        {"ZAid", 1, 12},
        {"Lara", 2, 18},
        {"Bilal", 3, 7},
        {"Aveen", 4, 25},
        {"Murtaza", 5, 15},
        {"Eman", 6, 9},
        {"Sara", 7, 30},
        {"Usman", 8, 5},
        {"Fida", 9, 20},
        {"Absar", 10, 14}
    };
    BST tree;
    cout << "Inserting 7 random students...\n";
    bool used[10] = {false};
    for (int i = 0; i < 7; i++) {
        int idx;
        do {
            idx = rand() % 10;
        } while (used[idx]);
        used[idx] = true;
        tree.insert(students[idx]);
    }
    tree.display();
    cout << "\nSearching for 'Sara'...\n";
    tree.search("Sara");
    cout << "\nDeleting students with score < 10...\n";
    tree.deleteLowScores();
    tree.display();
    tree.getMaxScore();
    return 0;
}
