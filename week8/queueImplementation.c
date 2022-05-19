#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CMD_LEN 20
#define TERMINATE_CMD "#"
struct Node {
    int val;
    struct Node *next;
};
typedef struct Node LinkedList;
void insertToLast(LinkedList **tail, int nodeVal){
    LinkedList *currentNode = (LinkedList*)malloc(sizeof(LinkedList));
    currentNode -> val = nodeVal;
    if (*tail) (*tail) -> next = currentNode;
    *tail = currentNode;
}
void deleteAtFront(LinkedList **head){
    LinkedList *currentNode = *head;
    *head = (*head) -> next;
    free(currentNode);
}
void readCommand(){
    LinkedList *head = NULL, *tail = NULL;
    char command[CMD_LEN];
    while ((scanf("%s", command)) && strcmp(command, TERMINATE_CMD)){
        if (strcmp(command, "PUSH") == 0){
            int arg;
            scanf("%d", &arg);
            insertToLast(&tail, arg);
            if (!head) head = tail;
            continue;
        }
        if (strcmp(command, "POP") == 0){
            if (head){
                printf("%d\n", head -> val);
                deleteAtFront(&head);
            } else {
                printf("NULL\n");
            }
        }
    }
}
int main(){
    readCommand();
}