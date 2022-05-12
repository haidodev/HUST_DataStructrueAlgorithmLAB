#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define COMMAND_LEN 20
struct Node {
    int val;
    struct Node *next;
};
typedef struct Node LinkedList;
void printLinkedList(LinkedList* node){
    while (node){
        printf("%d ", node -> val);
        node = node -> next;
    }
    printf("\n");
}
bool nodeExisted(LinkedList *node, int nodeVal){
    while (node){
        if (node -> val == nodeVal) return true;
        node = node -> next;
    } 
    return false;
}
void addFirst(LinkedList **node, int nodeVal){
    LinkedList *currentNode = *node;
    LinkedList *newNode = (LinkedList*)malloc(sizeof(LinkedList));
    newNode -> val = nodeVal;
    newNode -> next = currentNode;
    *node = newNode;
}
void addLast(LinkedList **node, int nodeVal){
    if (*node){
        addLast(&((*node) -> next), nodeVal);
        return;
    } 
    addFirst(node, nodeVal);
}
void addAfter(LinkedList **node, int nodeVal, int prevNode){
    if (!(*node)) return;
    if ((*node) -> val != prevNode){
        addAfter(&((*node) -> next), nodeVal, prevNode);
        return;
    }
    addFirst(&((*node) -> next), nodeVal);
}
void addBefore(LinkedList **node, int nodeVal, int prevNode){
    if (!(*node)) return;
    if ((*node) -> val != prevNode){
        addBefore(&((*node) -> next), nodeVal, prevNode);
        return;
    }
    addFirst(node, nodeVal);
}
void removeKey(LinkedList **node, int nodeVal){
    if (!(*node)) return;
    if ((*node) -> val != nodeVal){
        removeKey(&((*node) -> next), nodeVal);
        return;
    }
    LinkedList *nextNode = (*node) -> next;
    (*node) = nextNode;
}
void LinkedListToArr(LinkedList *node, LinkedList *nodeArr[1000], int *countNode){
    while (node){
        nodeArr[*countNode] = node;
        ++(*countNode);
        node = node -> next;
    }
}
void reverseLinkedList(LinkedList **node){
    LinkedList *nodeArr[1000];
    int countNode = 0;
    LinkedListToArr(*node, nodeArr, &countNode);
    for (int i = countNode - 1; i > 0; --i){
        nodeArr[i] -> next = nodeArr[i - 1];
    }
    nodeArr[0] -> next = NULL;
    (*node) = nodeArr[countNode - 1];
}
void buildLinkedList(LinkedList **node){
    int n;
    scanf("%d", &n);
    while (n--){
        int elm;
        scanf("%d", &elm);
        addLast(node, elm);
    }
}
void doCommands(LinkedList **node){
    char command[COMMAND_LEN];
    while ((scanf("%s", command)) && (strcmp(command, "#") != 0)){
        int arg1, arg2;
        if (strcmp(command, "addfirst") == 0){
            scanf("%d", &arg1);
            if (!nodeExisted(*node, arg1)) addFirst(node, arg1);
            continue;
        }
        if (strcmp(command, "addlast") == 0){
            scanf("%d", &arg1);
            if (!nodeExisted(*node, arg1)) addLast(node, arg1);
            continue;
        }
        if (strcmp(command, "addbefore") == 0){
            scanf("%d", &arg1);
            scanf("%d", &arg2);
            if (!nodeExisted(*node, arg1)) addBefore(node, arg1, arg2);
            continue;
        }
        if (strcmp(command, "addafter") == 0){
            scanf("%d", &arg1);
            scanf("%d", &arg2);
            if (!nodeExisted(*node, arg1)) addAfter(node, arg1, arg2);
            continue;
        }
        if (strcmp(command, "remove") == 0){
            scanf("%d", &arg1);
            removeKey(node, arg1);
            continue;
        }
        if (strcmp(command, "reverse") == 0){
            reverseLinkedList(node);
            continue;
        }
    }
}
int main(){
    LinkedList *node = NULL;
    buildLinkedList(&node);
    doCommands(&node);
    
    printLinkedList(node);
}