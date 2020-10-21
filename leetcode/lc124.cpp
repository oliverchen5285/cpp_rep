/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return recur(root).first;
    }
    pair<int, int> recur(TreeNode* root){
        int sum = root->val;
        int left_sum = 0;
        int right_sum = 0;
        int line = root->val;
        int left_line = 0;
        int right_line = 0;
        if(root->left != nullptr){
            pair<int, int> left_ans = recur(root->left);
            left_sum = left_ans.first;
            sum = max(sum, left_sum);
            
            left_line = left_ans.second;
            sum = max(sum, root->val + left_line);
            line = max(line, root->val + left_line);
            
        }
        if(root->right != nullptr){
            pair<int, int> right_ans = recur(root->right);
            right_sum = right_ans.first;
            sum = max(sum, right_sum);
            
            right_line = right_ans.second;
            sum = max(sum, root->val + right_line);
            line = max(line, root->val + right_line);
        }
        if(root->left != nullptr && root->right != nullptr){
            sum = max(sum, root->val + left_line + right_line);
        }
        //(cur), (left), (right), (cur + left), (cur + right), (cur + left + right)
        
        return {sum, line};
    }
    
};
