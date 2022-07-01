
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "tree.inp"
#define MAXLEN 256
#define min(a, b) (a) < (b) ? (a) : (b)
struct tnode
{
    struct tnode *left, *right;
    int val;
};
typedef struct tnode TreeNode;
struct qnode
{
    struct qnode *next;
    TreeNode **val;
};
typedef struct qnode Queue;
int string2int(char *str)
{
    if (str[0] == '-')
        return -string2int(str + 1);
    int res = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return res;
}
void modifyNode(TreeNode **root, char *nodeVal)
{
    if (strcmp(nodeVal, "null") == 0)
    {
        *root = NULL;
        return;
    }
    *root = (TreeNode *)malloc(sizeof(TreeNode));
    (*root)->val = string2int(nodeVal);
}
void removeNodeAtFront(Queue **head)
{
    Queue *curQueueNode = *head;
    (*head) = (*head)->next;
    free(curQueueNode);
}
void appendNodeAtBack(Queue **tail, TreeNode **root)
{
    Queue *newQueueNode = (Queue *)malloc(sizeof(Queue));
    newQueueNode->val = root;
    (*tail)->next = newQueueNode;
    (*tail) = (*tail)->next;
}
void printQueue(Queue *head)
{
    printf("Queue: ");
    while (head)
    {
        printf("%d\t", *(head->val) ? (*(head->val))->val : -100);
        head = head->next;
    }
    printf("End of Queue\n");
}
void printNode(TreeNode *root){
    if (!root)
    {
        printf("null\t");
        return;
    }
    printf("%d\t", root->val);
}
void printTreeInorder(TreeNode *root)
{
    {
        printf("\nnull");
        return;
    }
    printTreeInorder(root->left);
    printf("\nNODE: ");
    printNode(root);
    printf("left: ");
    printNode(root -> left);
    printf("right: ");
    printNode(root -> right);
    

    printTreeInorder(root->right);
}
void printTreePreorder(TreeNode *root)
{
    if (!root)
    {
        printf("null \t");
        return;
    }
    // printf("\nNODE: ");
    printNode(root);
    // printf("left: ");
    // printNode(root -> left);
    // printf("right: ");
    // printNode(root -> right);
    printTreePreorder(root->left);

    printTreePreorder(root->right);
}
void buildTree(TreeNode **root)
{
    FILE *fi = fopen(FILENAME, "r");
    // fi = stdin;
    char curNodeVal[MAXLEN];
    Queue *head = (Queue *)malloc(sizeof(Queue));
    head->val = root;
    Queue *tail = head;
    int cnt = 0, stt = 1000;
    while (fscanf(fi, "%s", curNodeVal) != -1)
    {
        if (!head)
            break;
        modifyNode(head->val, curNodeVal);

        TreeNode **curTreeNode = head->val;
        if (strcmp(curNodeVal, "null"))
        {
            (*curTreeNode)->left = NULL;
            appendNodeAtBack(&tail, &((*curTreeNode)->left));
            (*curTreeNode)->right = NULL;
            appendNodeAtBack(&tail, &((*curTreeNode)->right));
        }
        removeNodeAtFront(&head);
    }
    printf("PREORDER: ");
    printTreePreorder(*root);
    printf("\n");
}
int minimunPath(TreeNode *root){
    
    if (!root) return 0;
    int leftPath = minimunPath(root -> left), rightPath = minimunPath(root -> right);
    return min(root -> val + leftPath, root -> val + rightPath);
}
int main()
{
    TreeNode *root = NULL;
    buildTree(&root);
    printf("Minimun Path: %d", minimunPath(root));
}
