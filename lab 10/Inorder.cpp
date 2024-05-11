#include <iostream>
#include <climits>
#include <vector>
using namespace std;

struct TreeNode
{
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

    

    void display(TreeNode *root)
    {
        if (root != nullptr)
        {
            display(root->left);
            cout << root->val << "->";
            display(root->right);
        }
        cout<<"NULL"<<endl;
    }
};

int main()
{
    Solution solution;
    TreeNode *root1 = nullptr;
    int arr[7] = {40,20,60,10,30,70,25};
    for(int i = 0;i<7;i++)
    {
        root1 = solution.insertIntoBST(root1, arr[i]);
    }
    
    solution.display(root1);
    
    return 0;
}
