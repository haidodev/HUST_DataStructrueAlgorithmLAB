#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define COMMAND_LEN 20
struct Node {
    int val;
    struct Node *next;
};
typedef struct Node LinkedList;
void printPoly(LinkedList *node){
    while (node) {
        printf("%d ", node -> val);
        node = node -> next;
    }
    printf("\n");
}
void addFirst(LinkedList **node, int nodeVal){
    LinkedList *currentNode = *node;
    LinkedList *newNode = (LinkedList*)malloc(sizeof(LinkedList));
    newNode -> val = nodeVal;
    newNode -> next = currentNode;
    (*node) = newNode;
}
void addTerm(LinkedList **node, int coef, int exp){
    if ((*node) && (*node) -> next -> val > exp) {
        addTerm(&((*node) -> next -> next), coef, exp);
        return;
    }
    if ((*node) && (*node) -> next -> val == exp) {
        (*node) -> val += coef;
        return;
    }
    addFirst(node, exp);
    addFirst(node, coef);
}
int evaluatePoly(LinkedList *node, int variable_val){
    int res = 0;
    while (node){
        int coef = node -> val;
        node = node -> next;
        int exp = node -> val;
        node = node -> next;
        res += coef * pow(variable_val, exp);
    }
    return res;
}
void addPoly(LinkedList *node1, LinkedList *node2, LinkedList **node3){
    while (node1) {
        addTerm(node3, node1 -> val, node1 -> next -> val);
        node1 = node1 -> next -> next;
    }
    while (node2) {
        addTerm(node3, node2 -> val, node2 -> next -> val);
        node2 = node2 -> next -> next;
    }
}
void destroyPoly(LinkedList **node){
    if (!(*node)) return;
    destroyPoly(&((*node) -> next));
    free(*node);
}
void doCommands(LinkedList *nodeArr[]){
    char command[COMMAND_LEN];
    while ((scanf("%s", command)) && (strcmp(command, "*") != 0)){
        int arg1, arg2, arg3;
        if (strcmp(command, "Create") == 0){
            scanf("%d", &arg1);
            if (!nodeArr[arg1]) nodeArr[arg1] = NULL;
            continue;
        }
        if (strcmp(command, "AddTerm") == 0){
            scanf("%d %d %d", &arg1, &arg2, &arg3);
            addTerm(&nodeArr[arg1], arg2, arg3);
            continue;
        }
        if (strcmp(command, "EvaluatePoly") == 0){
            scanf("%d %d", &arg1, &arg2);
            printf("%d\n", evaluatePoly(nodeArr[arg1], arg2));
            continue;
        }
        if (strcmp(command, "AddPoly") == 0){
            scanf("%d %d %d", &arg1, &arg2, &arg3);
            destroyPoly(&nodeArr[arg3]);
            addPoly(nodeArr[arg1], nodeArr[arg2], &nodeArr[arg3]);
            continue;
        }
        if (strcmp(command, "PrintPoly") == 0){
            scanf("%d", &arg1);
            printPoly(nodeArr[arg1]);
            continue;
        }
        if (strcmp(command, "Destroy") == 0){
            scanf("%d", &arg1);
            destroyPoly(&nodeArr[arg1]);
            continue;
        }

    }
}
int main(){
    LinkedList *nodeArr[10001];
    doCommands(nodeArr);
}