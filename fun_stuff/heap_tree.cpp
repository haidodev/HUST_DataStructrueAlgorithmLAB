#include<bits/stdc++.h>
using namespace std;
typedef struct t_node {
    int val;
    struct t_node *left, *right;
} TreeNode;
void printNode(TreeNode* root){
    cout << "Val: " << root -> val;
    cout << ",left: ";
    if (root -> left) cout << root -> left -> val;
    else cout << "NULL";
    cout << ",right: ";
    if (root -> right) cout << root -> right -> val;
    else cout << "NULL";
    cout << endl;
}
void printTree(TreeNode *root){
    if (!root) return;
    printNode(root);
    printTree(root -> left);
    printTree(root -> right);
}
TreeNode* makeNode(int val){
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root -> val = val;
    root -> left = NULL;
    root -> right = NULL;
    return root;
}
int main(){
    ifstream fi("HEAP_TREE.INP");
    stack<TreeNode*> nodes;
    while (!fi.eof()){
        int val;
        fi >> val;
        TreeNode *newNode = makeNode(val);
        stack<TreeNode*> childNodes;
        TreeNode *tmpNode = NULL;
        while ((!nodes.empty()) && nodes.top() -> val > val){
            nodes.top() -> right = tmpNode;
            tmpNode = nodes.top();
            nodes.pop();
        }
        newNode -> left = tmpNode;
        nodes.push(newNode);
    }
    TreeNode *tmpNode = NULL;
    while (nodes.size()){
        nodes.top() -> right = tmpNode;
        tmpNode = nodes.top();
        nodes.pop();
    }
    printTree(tmpNode);
}