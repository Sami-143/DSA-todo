#include <iostream>
#include <algorithm>
using namespace std;
class node
{
public:
    int value;
    node *left;
    node *right;
    int height;

    node(int val)
    {
        value = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree
{
public:
    node *root;

    AVLTree()
    {
        root = nullptr;
    }

    int Height(node *n)
    {
        if (!n)
        {
            return 0;
        }
        return n->height;
    }

    int HeightDifference(node *n)
    {
        if (!n)
        {
            return 0;
        }
        return Height(n->left) - Height(n->right);
    }

    bool IsBalanced(node *n)
    {
        if (!n)
        {
            return true;
        }

        int balance = HeightDifference(n);

        // Check if the absolute height difference is less than or equal to 1 //another syntax is abs(balance)
        if (balance >= -1 && balance <= 1)
        {
            // Recursively check for balance in left and right subtrees
            return IsBalanced(n->left) && IsBalanced(n->right);
        }

        return false;
    }

    node *RR_rotation(node *&root)
    {
        node *newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        root->height = 1 + max(Height(root->left), Height(root->right));
        cout<<root->height<<endl;
        newRoot->height = 1 + max(Height(newRoot->left), Height(newRoot->right));
        cout<<newRoot->height<<endl;
        root = newRoot;
        return newRoot; // Add this line
    }

    // Similar changes for LL_rotation, LR_rotation, and RL_rotation

    node *LL_rotation(node *&root)
    {
        node *newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        root->height = 1 + max(Height(root->left), Height(root->right));
        cout<<root->height<<endl;
        newRoot->height = 1 + max(Height(newRoot->left), Height(newRoot->right));
        cout<<newRoot->height<<endl;
        root = newRoot;
        return newRoot; // Add this line
    }

    node *LR_rotation(node *&root)
    {
        LL_rotation(root->left);
        return RR_rotation(root);
    }

    node *RL_rotation(node *&root)
    {
        RR_rotation(root->right);
        return LL_rotation(root);
    }

    void InsertInAVL(int v)
    {
        root = Insert(root, v);
    }
    void DelFromAVL(int v)
    {
        root = Delete(root, v);
    }
    
private:
    // Helper function to insert a value into the AVL tree
    node *Insert(node *n, int v)
    {
        // Perform standard BST insertion
        if (!n)
        {
            return new node(v);
        }

        if (v < n->value)
        {
            n->left = Insert(n->left, v);
        }
        else if (v > n->value)
        {
            n->right = Insert(n->right, v);
        }
        else
        {
            // Duplicate values are not allowed in a BST
            return n;
        }

        // Update height of the current node
        n->height = 1 + max(Height(n->left), Height(n->right));

        // Check balance and perform rotations if needed
        int balance = HeightDifference(n);

        // Left Heavy
        if (balance > 1)
        {
            if (v < n->left->value)
            {
                // LL rotation
                LL_rotation(n);
            }
            else
            {
                // LR rotation
                LR_rotation(n);
            }
        }
        // Right Heavy
        else if (balance < -1)
        {
            if (v > n->right->value)
            {
                // RR rotation
                RR_rotation(n);
            }
            else
            {
                // RL rotation
                RL_rotation(n);
            }
        }

        return n;
    }

    private:
    node *Delete(node *n, int v)
    {
        // Standard BST deletion
        if (!n)
        {
            return n;
        }

        if (v < n->value)
        {
            n->left = Delete(n->left, v);
        }
        else if (v > n->value)
        {
            n->right = Delete(n->right, v);
        }
        else
        {
            // Node with the given value found

            if (!n->left || !n->right)
            {
                // Node with one child or no child
                node *temp = n->left ? n->left : n->right;

                if (!temp)
                {
                    // No child case
                    temp = n;
                    n = nullptr;
                }
                else
                {
                    // One child case
                    *n = *temp; // Copy the contents of the non-empty child
                }

                delete temp;
            }
            else
            {
                // Node with two children
                node *temp = FindMin(n->right); // Find the inorder successor
                n->value = temp->value;
                n->right = Delete(n->right, temp->value);
            }
        }

        if (!n)
        {
            return n; // If the tree had only one node, return
        }

        // Update height of the current node
        n->height = 1 + max(Height(n->left), Height(n->right));

        // Check balance and perform rotations if needed
        int balance = HeightDifference(n);

        // Left Heavy
        if (balance > 1)
        {
            if (HeightDifference(n->left) >= 0)
            {
                // LL rotation
                return LL_rotation(n);
            }
            else
            {
                // LR rotation
                return LR_rotation(n);
            }
        }
        // Right Heavy
        else if (balance < -1)
        {
            if (HeightDifference(n->right) <= 0)
            {
                // RR rotation
                return RR_rotation(n);
            }
            else
            {
                // RL rotation
                return RL_rotation(n);
            }
        }

        return n;
    }

    node *FindMin(node *n)
    {
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }
};


int main()
{
    AVLTree avlTree;

    // Insert values into AVL tree
    avlTree.InsertInAVL(10);
    avlTree.InsertInAVL(20);
    avlTree.InsertInAVL(30);
    avlTree.InsertInAVL(15);
    avlTree.InsertInAVL(5);

    // Display the tree structure or any other relevant information
    // (You may need to implement a display function)

    // Check if the tree is balanced
    if (avlTree.IsBalanced(avlTree.root))
    {
        cout << "Tree is balanced.\n";
    }
    else
    {
        cout << "Tree is not balanced.\n";
    }

    // Perform other operations like deletion if needed
    
    if (avlTree.IsBalanced(avlTree.root))
    {
        cout << "Tree is balanced.\n";
    }
    else
    {
        cout << "Tree is not balanced.\n";
    }
    // Display the tree structure after operations

    return 0;
}



//Leet Code Question 1
// class Solution {
//     vector<TreeNode*> temp;
// public:

//         void Inorder(TreeNode* root) {
//         if (root == nullptr) {
//             return;
//         }

//         Inorder(root->left);
//         temp.push_back(root); 
//         Inorder(root->right);
//     }

//         TreeNode* BinarySerachTree(int s, int e)
//         {
//             if (s > e)
//             {
//                 return nullptr;
//             }
//              int mid = s + (e - s)/2;
//              TreeNode *root = temp[mid];
//              root->left = BinarySerachTree(s, mid - 1);
//              root->right = BinarySerachTree(mid + 1, e);
//             return root;
//         }
//     TreeNode* balanceBST(TreeNode* root) {
//         Inorder(root);
//         return BinarySerachTree(0, temp.size()-1);
//     }
    
// };


//Leet Code Question 2
// class Solution {
// public:
//     int Height(TreeNode *n)
//     {
//         if (!n)
//         {
//             return 0;
//         }
//         return 1 + max(Height(n->left), Height(n->right));
//     }


//     int HeightDifference(TreeNode *n)
//     {
//         if (!n)
//         {
//             return 0;
//         }
//         return Height(n->left) - Height(n->right);
//     }
//     bool isBalanced(TreeNode *n)
//     {
//         if (!n)
//         {
//             return true;
//         }

//         int balance = HeightDifference(n);

//         if (balance >= -1 && balance <= 1)
//         {
//             // Recursively check for balance in left and right subtrees
//             return isBalanced(n->left) && isBalanced(n->right);
//         }

//         return false;
//     }
// };