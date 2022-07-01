#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 256
#define FILE_NAME "TRIE.INP"
typedef struct t_node {
    int val;
    struct t_node *leftMostChild, *adjacentChild;
} TreeNode;
TreeNode *MakeRoot(int nodeVal){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode -> val = nodeVal;
    newNode -> leftMostChild = NULL;
    newNode -> adjacentChild = NULL;
    return newNode;
}
void AppendAtBack(TreeNode **head, TreeNode *newNode){
    newNode -> adjacentChild = *head;
    (*head) = newNode;
}
void AppendChild(TreeNode *root, int childVal, int parentVal){
    if (!root) return;
    if (root -> val != parentVal) {
        AppendChild(root -> leftMostChild, childVal, parentVal);
        AppendChild(root -> adjacentChild, childVal, parentVal);
        return;
    }
    AppendAtBack(&(root -> leftMostChild), MakeRoot(childVal));

}
void preOrderTraversal(TreeNode *root){
    if (!root) return;
    printf("%d ", root -> val);
    preOrderTraversal(root -> leftMostChild);
    preOrderTraversal(root -> adjacentChild);
}
int CountNode(TreeNode *root){
    if (!root) return 0;
    int res = 1;

    TreeNode *tmp = root -> leftMostChild;
    while (tmp) {
        res += CountNode(tmp);
        tmp = tmp -> adjacentChild;
    }
    return res;
}
int CountLeaves(TreeNode *root){
    if (!root) return 0;
    if (root -> leftMostChild) {
        int res = 0;
        TreeNode *tmp = root -> leftMostChild;
        while (tmp) {
            res += CountLeaves(tmp);
            tmp = tmp -> adjacentChild;
        }
        return res;
    }
    return 1;
}
// int CountKChildren_(TreeNode* root, int k){
//     if (!root) return 0;
//     if (CountNode(root) <= k) return CountNode(root) == k;
//     int res = 0;
//     TreeNode *tmp = root -> leftMostChild;
//     while (tmp) {
//         res += CountKChildren(tmp, k);
//         tmp = tmp -> adjacentChild;
//     }
//     return res;
// }
int CountKChildren(TreeNode* root, int k){
    if (!root) return 0;
    int res = 0, count = 0;
    TreeNode *tmp = root -> leftMostChild;
    while (tmp) {
        ++count;
        res += CountKChildren(tmp, k);
        tmp = tmp -> adjacentChild;
    }
    return res + (count == k);
}
TreeNode *FindNode(TreeNode* root, int nodeVal){
    if (!root) return NULL;
    if (root -> val != nodeVal) {
        TreeNode* res = FindNode(root -> adjacentChild, nodeVal);
        if (res) return res;
        return FindNode(root -> leftMostChild, nodeVal);
    }
    return root;
}
void doCommands(){
    TreeNode *root = NULL;
    FILE *fi = stdin;
    char command[MAX_LEN];
    while (fscanf(fi, "%s", command) && strcmp(command, "*") != 0)
    {
        int arg1, arg2;
        if (strcmp(command, "MakeRoot") == 0){
            fscanf(fi, "%d", &arg1);
            root = MakeRoot(arg1);
        }
        if (strcmp(command, "Insert") == 0){
            fscanf(fi, "%d %d", &arg1, &arg2);
            AppendChild(root, arg1, arg2);
        }
        if (strcmp(command, "PreOrder") == 0){
            preOrderTraversal(root);
            printf("\n");
        } 
        if (strcmp(command, "CountLeaves") == 0){
            fscanf(fi, "%d", &arg1);
            printf("%d\n", CountLeaves(FindNode(root, arg1)));
        } 
        if (strcmp(command, "CountKChildren") == 0){
            fscanf(fi, "%d %d", &arg1, &arg2);
            printf("%d\n", CountKChildren(FindNode(root, arg1), arg2));
        } 
    }
}
int main(){
    doCommands();

}