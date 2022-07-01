#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_LEN 256
#define FILE_NAME "FAMILY.INP"
typedef struct t_node {
    char memberName[MAX_LEN];
    struct t_node *leftMostChild, *adjacentNode;
} TreeNode;
typedef struct l_node {
    bool isRoot;
    TreeNode *nodePtr;
    struct l_node *next;
} LinkedList;
TreeNode *createTreeNode(char *memberName){
    TreeNode *newTNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newTNode -> memberName, memberName);
    newTNode -> leftMostChild = NULL;
    newTNode -> adjacentNode = NULL;
    return newTNode;

}
LinkedList *createLinkedListNode(char *memberName){
    LinkedList *newLNode = (LinkedList*)malloc(sizeof(LinkedList));
    newLNode -> nodePtr = createTreeNode(memberName);
    newLNode -> isRoot = true;
    return newLNode;

}
LinkedList *findMember(char *memberName, LinkedList *head){
    while (head) {
        if (strcmp(memberName, head -> nodePtr -> memberName) == 0) return head;
        head = head -> next;
    }
    return NULL;
}
void appendLNodeToFront(LinkedList **head, LinkedList *newLNode){
    newLNode -> next = *head;
    *head = newLNode;
}
void appendChild(TreeNode *childNode, TreeNode *parentNode){
    childNode -> adjacentNode = parentNode -> leftMostChild;
    parentNode -> leftMostChild = childNode;
}
void linkFamilyMember(char *childName, char *parentName, LinkedList **head){
    LinkedList *childLNode, *parentLNode;
    childLNode = findMember(childName, *head);
    if (!childLNode) {
        appendLNodeToFront(head, createLinkedListNode(childName));
        childLNode = (*head);
    }
    childLNode -> isRoot = false;
    parentLNode = findMember(parentName, *head);
    if (!parentLNode) {
        appendLNodeToFront(head, createLinkedListNode(parentName));
        parentLNode = (*head);
    }
    appendChild(childLNode -> nodePtr, parentLNode -> nodePtr);
}
TreeNode *findRoot(LinkedList *head) {
    while (head) {
        if (head -> isRoot) return head -> nodePtr;
        head = head -> next;
    }
    return NULL;
}
TreeNode *findNode(TreeNode *root, char *memberName){
    if (!root) return NULL;
    if (strcmp(root -> memberName, memberName) != 0){
        TreeNode *tmpNode = root -> leftMostChild;
        while (tmpNode) {
            TreeNode *cur = findNode(tmpNode, memberName);
            if (cur) return cur;
            tmpNode = tmpNode -> adjacentNode;
        }
        return NULL;
    }
    return root;
}
int countDescendants(TreeNode *root){
    if (!root) return 0;
    int res = 0;
    TreeNode *tmpNode = root -> leftMostChild;
    while (tmpNode) {
        res += (countDescendants(tmpNode) + 1);
        tmpNode = tmpNode -> adjacentNode;
    }
    return res;
}
int countGeneration(TreeNode *root, char *memberName, int curGen){
    if (!root) return -1;
    if (strcmp(root -> memberName, memberName) != 0){
        TreeNode *tmpNode = root -> leftMostChild;
        while (tmpNode) {
            int cur = countGeneration(tmpNode, memberName, curGen + 1);
            if (cur != -1) return cur;
            tmpNode = tmpNode -> adjacentNode;
        }
        return -1;
    }
    return curGen;
}
void printTreeNode(TreeNode *root){
    if (!root) return;
    printf("%s: ", root -> memberName);
    TreeNode *tmpNode = root -> leftMostChild;
    while (tmpNode) {
        printf("%s ", tmpNode -> memberName);
        tmpNode = tmpNode -> adjacentNode;
    }
    printf("\n");
}
void preOrderTraversal(TreeNode *root){
    if (!root) return;
    printTreeNode(root);
    TreeNode *tmpNode = root -> leftMostChild;
    while (tmpNode){
        preOrderTraversal(tmpNode);
        tmpNode = tmpNode -> adjacentNode;
    } 
}
void doCommands(){
    LinkedList *head = NULL;
    FILE *fi = stdin;
    int cnt = 0;
    while (true)
    {
        char childName[MAX_LEN];
        fscanf(fi, "%s", childName);
        if (strcmp(childName, "***") == 0) break;
        char parentName[MAX_LEN];
        fscanf(fi, "%s", parentName);
        linkFamilyMember(childName, parentName, &head);
    }
    TreeNode *root = findRoot(head);
    char command[MAX_LEN];
    while (fscanf(fi, "%s", command) && strcmp(command, "***") != 0)
    {
        char memberName[MAX_LEN];
        fscanf(fi, "%s", memberName);
        TreeNode *curNode = findNode(root, memberName);
        if (strcmp(command, "descendants") == 0){
            printf("%d\n", countDescendants(curNode));
        }
        if (strcmp(command, "generation") == 0){
            printf("%d\n", countGeneration(root, memberName, 1));
        }
        
    }
    
}
int main(){
    doCommands();
}