#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INP_FILE "TREE.INP"
#define MAX_LEN 256
typedef struct t_node {
    int val;
    struct t_node *left, *right;
} TreeNode;
typedef struct q_node {
    TreeNode** nodePointer;
    struct q_node *next;
} Queue;
void printNode(TreeNode *root){
    printf("nodeVal: %d, ", root -> val);
    printf("Left: ");
    if (root -> left) printf("%d ", root -> left -> val);
    else printf("null, ");
    printf("Right: ");
    if (root -> right) printf("%d \n", root -> right -> val);
    else printf("null\n");
}
void inorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    inorderTraversal(root -> left);
    printNode(root);
    inorderTraversal(root -> right);
}
void preorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    printNode(root);
    preorderTraversal(root -> left);
    preorderTraversal(root -> right);
}
void postorderTraversal(TreeNode *root){
    if (!root){
        return;
    }
    postorderTraversal(root -> left);
    postorderTraversal(root -> right);
    printNode(root);
}
void createNewNode(TreeNode **root, int nodeVal){
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode -> val = nodeVal;
    newNode -> left = NULL;
    newNode -> right = NULL;
    *root = newNode;
}
void QueuePushBack(Queue **head, Queue **tail, TreeNode **nodePtr){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    newNode -> nodePointer = nodePtr;
    if (*tail) (*tail) -> next = newNode;
    else *head = newNode;
    *tail = newNode;
}
void QueuePopFront(Queue **head, Queue **tail){
    Queue *tmpNode = *head;
    if (*head == *tail) {
        *head = NULL;
        *tail = NULL;
    } else *head = (*head) -> next;
    free(tmpNode);
    
}
void buildTree(TreeNode **root){
    FILE *fi = fopen(INP_FILE, "r");
    Queue *head = NULL, *tail = NULL;
    QueuePushBack(&head, &tail, root);
    while (!feof(fi)){
        char nodeVal[MAX_LEN];
        fscanf(fi, "%s", nodeVal);
        if (strcmp(nodeVal, "null")){
            int val;
            sscanf(nodeVal, "%d", &val);
            createNewNode(head -> nodePointer, val);
            TreeNode *curNode = *(head -> nodePointer);
            QueuePushBack(&head, &tail, &(curNode -> left));
            QueuePushBack(&head, &tail, &(curNode -> right));
        }
        QueuePopFront(&head, &tail);
    }

}
int main(){
    TreeNode *root = NULL;
    buildTree(&root);
    preorderTraversal(root);
}