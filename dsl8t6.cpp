//inventory management sysren
#include <iostream>
using namespace std;

struct InventoryNode {
    int productId;
    int quantity;
    InventoryNode *left, *right;

    InventoryNode(int id, int qty)
        : productId(id), quantity(qty), left(nullptr), right(nullptr) {}
};

class InventoryBST {
private:
    InventoryNode* root;

    InventoryNode* insertRec(InventoryNode* node, int id, int qty) {
        if (!node) return new InventoryNode(id, qty);

        if (id < node->productId)
            node->left = insertRec(node->left, id, qty);
        else if (id > node->productId)
            node->right = insertRec(node->right, id, qty);

        return node;
    }

    void findMaxRec(InventoryNode* node, int &maxQty, int &maxId) {
        if (!node) return;

        if (node->quantity > maxQty) {
            maxQty = node->quantity;
            maxId = node->productId;
        }

        findMaxRec(node->left, maxQty, maxId);
        findMaxRec(node->right, maxQty, maxId);
    }

public:
    InventoryBST() : root(nullptr) {}

    void insertProduct(int id, int qty) {
        root = insertRec(root, id, qty);
    }

    InventoryNode* searchProduct(int id) {
        InventoryNode* cur = root;
        while (cur) {
            if (id == cur->productId) return cur;
            else if (id < cur->productId) cur = cur->left;
            else cur = cur->right;
        }
        return nullptr;
    }

    bool updateQuantity(int id, int qty) {
        InventoryNode* p = searchProduct(id);
        if (!p) return false;
        p->quantity = qty;
        return true;
    }

    pair<int,int> highestQuantityProduct() {
        int maxQty = -1, maxId = -1;
        findMaxRec(root, maxQty, maxId);
        return {maxId, maxQty};
    }
};

int main() {
    InventoryBST inv;

    inv.insertProduct(101, 50);
    inv.insertProduct(103, 80);
    inv.insertProduct(105, 120);

    inv.updateQuantity(105, 150);

    auto x = inv.highestQuantityProduct();
    cout << "Highest Stock Product ID: " << x.first
         << ", Quantity: " << x.second;

    return 0;
}
