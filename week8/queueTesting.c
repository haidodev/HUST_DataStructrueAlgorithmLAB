#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct tnode {
    struct tnode *left, *right;
    int val;
};
typedef struct tnode TreeNode;
struct qnode {
    struct qnode *next;
    TreeNode *val;
};
typedef struct qnode Queue; 
void removeNodeAtFront(Queue **head){
    Queue *curNode = *head;
    (*head) = (*head) -> next;
    free(curNode);
}
void appendNodeAtBack(Queue **tail, TreeNode *root){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    newNode -> val = root;
    (*tail) -> next = newNode;
    (*tail) = (*tail) -> next;
}
void printQueue(Queue *head){
    printf("Queue: ");
    while (head){ 
        printf("%d\t", head -> val -> val);
        head = head -> next;
    }
    printf("\n");
}
void itoa(int n, char* str){
    int arr[100];
    if (n == 0){
        str[0] = '0';
        str[1] = 0;
    }
    int len = 0;
    while (n){
        arr[len++] = n % 10;
        n /= 10;
    }
    for (int i = len  -1;i >= 0; --i) str[i] = '0' + arr[len - i - 1];
    str[len] = 0;
}
void QueueTesting(){
    
    TreeNode *root = (TreeNode*) malloc(sizeof(TreeNode));
    root -> val = 1;
    Queue *head = (Queue *)malloc(sizeof(Queue));
    head -> val = root;
    Queue *tail = head;
    for (int i = 2; i < 5; ++i){
        TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));
        newNode -> val = i;
        appendNodeAtBack(&tail, newNode);
    }
    printQueue(head);
    removeNodeAtFront(&head);
    printQueue(head);
    removeNodeAtFront(&head);
    printQueue(head);
    removeNodeAtFront(&head);
    printQueue(head);


}
int main(){
    TreeNode *root = NULL;
    QueueTesting();
}