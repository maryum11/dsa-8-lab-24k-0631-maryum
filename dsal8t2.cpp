#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;
struct Combatant{
    string name;
    int id;
    int hp;
    int ap;
    Combatant() {}
    Combatant(string n, int i, int h, int a) {
        name=n;
        id=i;
        hp=h;
        ap=a;
    }
};
struct Node{
    Combatant data;
    Node* left;
    Node* right;

    Node(Combatant c) {
        data = c;
        left = right = nullptr;
    }
};
class BST{
private:
    Node* root;

    Node* insert(Node* node, Combatant c) {
        if (!node) return new Node(c);
        if (c.id < node->data.id)
            node->left = insert(node->left, c);
        else if (c.id > node->data.id)
            node->right = insert(node->right, c);
        return node;
    }
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }
    Node* deleteNode(Node* node, int id) {
        if (!node) return node;
        if (id < node->data.id)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.id)
            node->right = deleteNode(node->right, id);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.id);
        }
        return node;
    }
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data.name << "(" << node->data.hp << " HP)  ";
        inorder(node->right);
    }
public:
    BST() { root = nullptr; }

    void insert(Combatant c) { root = insert(root, c); }
    void deleteById(int id) { root = deleteNode(root, id); }

    bool isEmpty() { return root == nullptr; }

    Node* getFrontline() { return findMin(root); }

    void displayTeam() {
        inorder(root);
        cout << endl;
    }
};
class BattleQuest {
private:
    BST heroes;
    BST enemies;
    int round;
public:
    BattleQuest() {
        round = 1;
        srand(time(0)); 
        initializeTeams();
    }
    void initializeTeams() {
        heroes.insert(Combatant("Knight", 10, 40, 8));
        heroes.insert(Combatant("Archer", 5, 30, 10));
        enemies.insert(Combatant("Skeleton", 18, 20, 8));
        enemies.insert(Combatant("Vampire", 11, 35, 10));
    }
    void displayStatus() {
        cout << "\n Round " << round << " " << endl;
        cout << "\n-- Heroes --\n";
        heroes.displayTeam();
        cout << "\n-- Enemies --\n";
        enemies.displayTeam();
    }
    void startBattle() {
        cout << "\n?? Welcome to BattleQuest: BST Arena \n";
        while (!heroes.isEmpty() && !enemies.isEmpty()) {
            displayStatus();
            Node* heroNode = heroes.getFrontline();
            Node* enemyNode = enemies.getFrontline();

            if (!heroNode || !enemyNode)
                break;
            Combatant &hero = heroNode->data;
            Combatant &enemy = enemyNode->data;
            int heroDamage = hero.ap + rand() % 5;
            cout << hero.name << " attacks " << enemy.name << " for " << heroDamage << " damage!\n";
            enemy.hp -= heroDamage;
            if (enemy.hp <= 0) {
                cout << enemy.name << " is defeated!\n";
                enemies.deleteById(enemy.id);
            }
            if (!enemies.isEmpty()) {
                Node* newEnemyNode = enemies.getFrontline();
                Combatant &newEnemy = newEnemyNode->data;

                int enemyDamage = newEnemy.ap + rand() % 5;
                cout << newEnemy.name << " attacks " << hero.name << " for " << enemyDamage << " damage!\n";
                hero.hp -= enemyDamage;
                if (hero.hp <= 0) {
                    cout << hero.name << " has fallen!\n";
                    heroes.deleteById(hero.id);
                }
            }
            round++;
        }
        if (heroes.isEmpty())
            cout <<"\n All heroes defeated! Enemies win!\n";
        else
            cout <<"\nAll enemies defeated! Heroes win!\n";
    }
};
int main() {
    BattleQuest game;
    game.startBattle();
    return 0;
}
