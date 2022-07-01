#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 256
#define FILE_NAME "TRIE.INP"
#define MAX(a, b) (a) > (b) ? (a) : (b)
typedef struct t_node {
    int val;
    struct t_node *leftMostChild, *rightMostChild, *adjacentChild;
} TreeNode;
TreeNode* MakeRoot(int nodeVal){
    TreeNode* newTNode = (TreeNode*)malloc(sizeof(TreeNode));
    newTNode -> val = nodeVal;
    newTNode -> leftMostChild = NULL;
    newTNode -> rightMostChild = NULL;
    newTNode -> adjacentChild = NULL;
    return newTNode;
}
void printTreeNode(TreeNode *root){
    if (!root) return;
    printf("%d ", root -> val);
}
void preOrderTraversal(TreeNode *root){
    if (!root) return;
    printTreeNode(root);
    TreeNode *tmpNode = root -> leftMostChild;
    while (tmpNode){
        preOrderTraversal(tmpNode);
        tmpNode = tmpNode -> adjacentChild;
    } 
}

void inOrderTraversal(TreeNode *root){
    if (!root) return;
    if (root -> leftMostChild) inOrderTraversal(root -> leftMostChild);
    printTreeNode(root);
    if (!root -> leftMostChild) return;
    TreeNode *tmpNode = root -> leftMostChild -> adjacentChild;
    while (tmpNode){
        inOrderTraversal(tmpNode);
        tmpNode = tmpNode -> adjacentChild;
    } 
    
}
void postOrderTraversal(TreeNode *root){
    if (!root) return;
    TreeNode *tmpNode = root -> leftMostChild;
    while (tmpNode){
        postOrderTraversal(tmpNode);
        tmpNode = tmpNode -> adjacentChild;
    } 
    printTreeNode(root);
}
void newPreOrder(TreeNode *root){
    if (!root) return;
    printf("%d ", root -> val);
    newPreOrder(root -> leftMostChild);
    newPreOrder(root -> adjacentChild);
}
int countNode(TreeNode *root){
    if (!root) return 0;
    return 1 + countNode(root -> leftMostChild) + countNode(root -> adjacentChild);
}
int countLeaves(TreeNode *root){
    if (!root) return 0;
    if (root -> leftMostChild) return countLeaves(root -> adjacentChild) + countLeaves(root -> leftMostChild);
    return 1 + countLeaves(root -> adjacentChild);
}
int treeHeight(TreeNode *root){
    if (!root) return 0;
    return MAX(1 + treeHeight(root -> leftMostChild), treeHeight(root -> adjacentChild));
}
void newPostOrder(TreeNode *root){
    if (!root) return;
    newPostOrder(root -> leftMostChild);
    printf("%d ", root -> val);
    newPostOrder(root -> adjacentChild);
}
void appendAtBack(TreeNode **head, TreeNode **tail, TreeNode *root){
    if (*tail) (*tail) -> adjacentChild = root;
    else *head = root;
    *tail = root;
}
void AppendChild(TreeNode *root, int childNode, int parentNode){
    if (!root) return;
    if (root -> val != parentNode) {
        TreeNode *tmpNode = root -> leftMostChild;
        while (tmpNode){
            AppendChild(tmpNode, childNode, parentNode);
            tmpNode = tmpNode -> adjacentChild;
        } 
        return;
    } 
    TreeNode *newTNode = MakeRoot(childNode);
    appendAtBack(&(root -> leftMostChild), &(root -> rightMostChild), newTNode);
}
void doCommands(){
    TreeNode *root = NULL;
    FILE *fi = fopen(FILE_NAME, "r");
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
        if (strcmp(command, "InOrder") == 0){
            inOrderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "PreOrder") == 0){
            preOrderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "PostOrder") == 0){
            postOrderTraversal(root);
            printf("\n");
        }
        if (strcmp(command, "CountNode") == 0){
            printf("%d\n", countNode(root));
        }
        if (strcmp(command, "CountLeaves") == 0){
            printf("%d\n", countLeaves(root));
        }
        if (strcmp(command, "TreeHeight") == 0){
            printf("%d\n", treeHeight(root));
        }
        
    }
    
}
int main(){
    doCommands();

}