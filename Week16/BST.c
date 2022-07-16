#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 256
typedef struct t_node {
    int val;
    struct t_node *left, *right;
} TreeNode;
TreeNode *makeNode(int nodeVal){
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode -> val = nodeVal;
    return newNode;
}
void preOrderTraversal(TreeNode *root){
    if (!root) return;
    printf("%d ", root -> val);
    preOrderTraversal(root -> left);
    preOrderTraversal(root -> right);
}
void postOrderTraversal(TreeNode *root){
    if (!root) return;
    postOrderTraversal(root -> left);
    postOrderTraversal(root -> right);
    printf("%d ", root -> val);
}
void insertNode(TreeNode **rootPtr, int nodeVal){
    if (!rootPtr) return;
    if (!(*rootPtr)){
        *rootPtr = makeNode(nodeVal);
        return;
    }
    if ((*rootPtr) -> val == nodeVal) return;
    if ((*rootPtr) -> val > nodeVal){
        insertNode(&((*rootPtr) -> left), nodeVal);
    } else {
        insertNode(&((*rootPtr) -> right), nodeVal);
    }

}
void doCommands(){
    TreeNode *root = NULL;
    char command[MAXLEN];
    while (scanf("%s", command) && strcmp(command, "#") != 0){
        if (strcmp(command, "insert") == 0){
            int nodeVal;
            scanf("%d", &nodeVal);
            insertNode(&root, nodeVal);
        }
        if (strcmp(command, "preorder") == 0){
            preOrderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "postorder") == 0){
            postOrderTraversal(root);
            printf("\n");
        }
    }
}
int main(){
    doCommands();
}