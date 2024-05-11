#include <iostream>
#include <cstdlib>  // for rand() function
using namespace std;

class RandomizedBinarySearchTree {
private:
    struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    // Function to perform a right rotation
    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }

    // Function to perform a left rotation
    TreeNode* rotateLeft(TreeNode* node) {
        TreeNode* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }

    // Function to insert a key into the tree
    TreeNode* insert(TreeNode* root, int key) {
        if (!root) {
            return new TreeNode(key);
        }

        // Randomly decide whether to go left or right during insertion
        if (rand() % (root->key + 1) == 0) {
            root->left = insert(root->left, key);
            root = rotateRight(root);
        } else {
            root->right = insert(root->right, key);
            root = rotateLeft(root);
        }

        return root;
    }

    // Function to search for a key in the tree
    bool search(TreeNode* root, int key) {
        if (!root) {
            return false;
        }

        if (root->key == key) {
            return true;
        } else if (key < root->key) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }

public:
    RandomizedBinarySearchTree() : root(nullptr) {}

    // Public function to insert a key
    void insert(int key) {
        root = insert(root, key);
    }

    // Public function to search for a key
    bool search(int key) {
        return search(root, key);
    }
};

int main() {
    RandomizedBinarySearchTree tree;

    // Insert some keys
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    // Search for keys
    cout << "Search for 4: " << (tree.search(4) ? "Found" : "Not Found") << endl;
    cout << "Search for 6: " << (tree.search(6) ? "Found" : "Not Found") << endl;

    return 0;
}

