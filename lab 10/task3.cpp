#include <iostream>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            return new TreeNode(val);
        }

        if (val < root->val)
        {
            root->left = insertIntoBST(root->left, val);
        }
        else if (val > root->val)
        {
            root->right = insertIntoBST(root->right, val);
        }

        return root;
    }

    bool Identical(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }

        if (root1 != nullptr && root2 != nullptr)
        {
            return (root1->val == root2->val) && Identical(root1->left, root2->left) && Identical(root1->right, root2->right);
        }

        return false;
    }
    void display(TreeNode *root)
    {
        if (root != nullptr)
        {
            display(root->left);
            cout << root->val << "->";
            display(root->right);
        }
    }
};

int main()
{

    Solution solution;
    TreeNode *root1 = nullptr;
    root1 = solution.insertIntoBST(root1, 40);
    solution.insertIntoBST(root1, 20);
    solution.insertIntoBST(root1, 60);
    solution.insertIntoBST(root1, 10);
    solution.insertIntoBST(root1, 30);
    solution.insertIntoBST(root1, 70);
    solution.insertIntoBST(root1, 25);

    TreeNode *root2 = nullptr;
    root2 = solution.insertIntoBST(root2, 40);
    solution.insertIntoBST(root2, 20);
    solution.insertIntoBST(root2, 60);
    solution.insertIntoBST(root2, 11);
    solution.insertIntoBST(root2, 30);
    solution.insertIntoBST(root2, 70);
    solution.insertIntoBST(root2, 25);

    solution.display(root1);
    cout<<endl;
    solution.display(root2);
    cout<<endl;
    if (solution.Identical(root1, root2))
    {
        cout << "Identical" << endl;
    }

    else
    {
        cout << "not Identical" << endl;
    }
    return 0;
}



