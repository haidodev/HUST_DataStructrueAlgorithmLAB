#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 256
#define FILE_NAME "TREE.INP"
typedef struct t_node {
    int val;
    struct t_node *left, *right;
} TreeNode;

void inorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    inorderTraversal(root -> left);
    printf("%d ", root -> val);
    inorderTraversal(root -> right);
}
void preorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    printf("%d ", root -> val);
    preorderTraversal(root -> left);
    preorderTraversal(root -> right);
}
void postorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    postorderTraversal(root -> left);
    postorderTraversal(root -> right);
    printf("%d ", root -> val);
}

TreeNode* MakeRoot(int nodeVal){
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode -> val = nodeVal;
    return newNode;
}
void AddLeft(TreeNode *root, int childNode, int parentNode){
    if (!root) return;
    if (root -> val != parentNode) {
        AddLeft(root -> left, childNode, parentNode);
        AddLeft(root -> right, childNode, parentNode);
        return;
    }
    if (root -> left) return;
    root -> left = MakeRoot(childNode);
}
void AddRight(TreeNode *root, int childNode, int parentNode){
    if (!root) return;
    if (root -> val != parentNode) {
        AddRight(root -> left, childNode, parentNode);
        AddRight(root -> right, childNode, parentNode);
        return;
    }
    if (root -> right) return;
    root -> right = MakeRoot(childNode);
}

void doCommands(){
    TreeNode *root = NULL;
    char command[MAX_LEN];
    while (scanf("%s", command) && strcmp(command, "*") != 0)
    {
        int arg1, arg2;
        if (strcmp(command, "MakeRoot") == 0){
            scanf("%d", &arg1);
            root = MakeRoot(arg1);
        }
        if (strcmp(command, "AddLeft") == 0){
            scanf("%d %d", &arg1, &arg2);
            AddLeft(root, arg1, arg2);
        }
        if (strcmp(command, "AddRight") == 0){
            scanf("%d %d", &arg1, &arg2);
            AddRight(root, arg1, arg2);
        }
        if (strcmp(command, "InOrder") == 0){
            inorderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "PreOrder") == 0){
            preorderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "PostOrder") == 0){
            postorderTraversal(root);
            printf("\n");
        }
        
    }
    
}
int main(){
    doCommands();
    
}