#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TERMINATE_CMD "#"
#define CMD_LEN 10
struct Node {
    int val;
    struct Node *next;
};
typedef struct Node LinkedList;
void insertToFront(LinkedList **head, int nodeVal){
    LinkedList *currentNode = (LinkedList*)malloc(sizeof(LinkedList));
    currentNode -> val = nodeVal;
    currentNode -> next = *head;
    *head = currentNode;
}
void deleteAtFront(LinkedList **head){
    if (!head) return;
    LinkedList *currentNode = *head;
    *head = (*head) -> next;
    free(currentNode);
}
void readCommand(){
    LinkedList *head = NULL;
    char command[CMD_LEN];
    while ((scanf("%s", command)) && strcmp(command, TERMINATE_CMD) != 0){
        int arg;
        if (strcmp(command, "PUSH") == 0){
            scanf("%d", &arg);
            insertToFront(&head, arg);
            continue;
        }
        if (strcmp(command, "POP") == 0){
            if (head){
                printf("%d\n", head -> val);
                deleteAtFront(&head);
            }
            else {
                printf("NULL\n");
            }
            continue;
        }
    }
}
int main(){
    readCommand();
}