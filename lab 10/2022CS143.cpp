#include <iostream>
#include <climits>
#include <vector>
#include<queue>
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

    // Helper function for searching a value in the BST recursively
    bool searchInBST(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            return false;
        }

        if (val == root->val)
        {
            return true;
        }
        else if (val < root->val)
        {
            return searchInBST(root->left, val);
        }
        else
        {
            return searchInBST(root->right, val);
        }
    }

    int Counter(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int count = 0;
        if (root->val % 2 == 0)
        {
            count++;
        }

        count += Counter(root->left);
        count += Counter(root->right);

        return count;
    }

    int Height(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int leftHeight = Height(root->left);
        int rightHeight = Height(root->right);

        // The height of the tree is the maximum height of its left and right subtrees, plus 1 for the root level.
        return 1 + max(leftHeight, rightHeight);
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

    bool ValidateHelper(TreeNode *root, int min_Value, int max_Value)
    {
        if (root == nullptr)
        {
            return true;
        }

        // Check if the current node's value is outside the valid range
        if (root->val <= min_Value || root->val >= max_Value)
        {
            return false;
        }

        // Recursively check the left and right subtrees
        return ValidateHelper(root->left, min_Value, root->val) && ValidateHelper(root->right, root->val, max_Value);
    }

    int leaves_Counter(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        // Check if the node is a leaf
        if (root->left == nullptr && root->right == nullptr)
        {
            return 1;
        }

        int leftLeaves = leaves_Counter(root->left);
        int rightLeaves = leaves_Counter(root->right);

        return leftLeaves + rightLeaves;
    }


    int One_Branch_Counter(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        // Check if the node has exactly one child
        if ((root->left != nullptr && root->right == nullptr) || (root->left == nullptr && root->right != nullptr))
        {
            return 1;
        }

        // Recursively count nodes with exactly one branch in the left and right subtrees
        int leftCount = One_Branch_Counter(root->left);
        int rightCount = One_Branch_Counter(root->right);

        // Sum up the counts
        return leftCount + rightCount;
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
    int arr[7] = {40,20,60,10,30,70,25};
    for(int i = 0;i<7;i++)
    {
        root1 = solution.insertIntoBST(root1, arr[i]);
    }

    TreeNode *root2 = nullptr;
    int arr1[7] = {40,20,60,11,30,70,25};
    for(int i = 0;i<7;i++)
    {
        root2 = solution.insertIntoBST(root2, arr1[i]);
    }

    solution.display(root1);
    cout << endl;
    solution.display(root2);

    cout << endl;
    if (solution.searchInBST(root1,20))
    {
        cout << "Exist!" << endl;
    }
    cout << endl;
    if (solution.Identical(root1, root2))
    {
        cout << "Oops!Not Exist." << endl;
    }

    else
    {
        cout << "not Identical" << endl;
    }

    cout << endl;
    cout << solution.Counter(root1);

    cout << endl;
    cout << solution.Height(root1);

    cout << endl;
    // Call ValidateHelper to check if the tree is a BST
    if (solution.ValidateHelper(root1, INT_MIN, INT_MAX))
    {
        cout << "The given binary tree is a Binary Search Tree (BST)." << endl;
    }
    else
    {
        cout << "The given binary tree is not a Binary Search Tree (BST)." << endl;
    }

    cout << endl;
    cout << solution.leaves_Counter(root1);

    cout << endl;
    cout << solution.One_Branch_Counter(root1);
}


//Task 4 (a,b,c)

// class Solution
// {
//     vector<int> inorder;
//     void inOrder(TreeNode* root)
//     {
//         if (root == nullptr)
//         {
//             return;
//         }
//         inorderTraversal(root->left);
//         inorder.push_back(root->val);
//         inorderTraversal(root->right);

//     }
// public:
//     vector<int> inorderTraversal(TreeNode *root)
//     {
//         inOrder(root);
//         return inorder;
//     }
// };

// class Solution1 {
//     vector<int> post_order;
//     void Post_Order(TreeNode* root)
//     {
//         if (root == nullptr)
//         {
//             return;
//         }
//         postorderTraversal(root->left);
//         postorderTraversal(root->right);
//         post_order.push_back(root->val);

//     }
// public:
//     vector<int> postorderTraversal(TreeNode* root) {
//         Post_Order(root);
//         return post_order;
//     }
// };

// class Solution2 {
//     vector<int> pre_order;
//     void Pre_Order(TreeNode* root)
//     {
//         if (root == nullptr)
//         {
//             return;
//         }
//         pre_order.push_back(root->val);
//         preorderTraversal(root->left);
//         preorderTraversal(root->right);
//     }
// public:
//     vector<int> preorderTraversal(TreeNode* root) {
//         Pre_Order(root);
//         return pre_order;
//     }
// };

//Level Treversal (Task 5)
// class Solution
// {
// public:
//     vector<vector<int>> levelOrder(TreeNode *root)
//     {
//         vector<vector<int>> result;
//         if (root == nullptr)
//         {
//             return result;
//         }

//         queue<TreeNode *> que;
//         que.push(root);
//         que.push(nullptr);

//         vector<int> level;
//         while (!que.empty())
//         {
//             TreeNode *node = que.front();
//             que.pop();

//             if (node != nullptr)
//             {
//                 level.push_back(node->val);

//                 if (node->left)
//                 {
//                     que.push(node->left);
//                 }
//                 if (node->right)
//                 {
//                     que.push(node->right);
//                 }
//             }
//             else
//             {
//                 result.push_back(level);
//                 level.clear();
//                 if (!que.empty())
//                 {
//                     que.push(nullptr);
//                 }
//             }
//         }
//         return result;
//     }
// };


// template <typename> T
//int countSingleBranchNodes(TreeNode<T>* root) {
//     if (root == nullptr) {
//         return 0;
//     }

//     int count = 0;

//     // Using level order traversal (BFS)
//     queue<TreeNode<T>*> q;
//     q.push(root);

//     while (!q.empty()) {
//         TreeNode<T>* current = q.front();
//         q.pop();

//         // Check if the current node is internal with exactly one branch out
//         if ((current->left != nullptr && current->right == nullptr) ||
//             (current->left == nullptr && current->right != nullptr)) {
//             count++;
//         }

//         // Enqueue child nodes
//         if (current->left != nullptr) {
//             q.push(current->left);
//         }
//         if (current->right != nullptr) {
//             q.push(current->right);
//         }
//     }

//     return count;
// }