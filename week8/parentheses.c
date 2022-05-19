#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define STR_LEN 1000001
struct Node {
    char val;
    struct Node *next;
};
typedef struct Node LinkedList;
void insertToFront(LinkedList **head, char nodeVal){
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
int isClosingBracket(char c){
    if (c == ')') return 1;
    if (c == ']') return 2;
    if (c == '}') return 3;
    return -1;
}
int isOpeningBracket(char c){
    if (c == '(') return 1;
    if (c == '[') return 2;
    if (c == '{') return 3;
    return -1;
}
bool validParentheses(char *str){
    LinkedList *stack = NULL;
    for (int i = 0; i < strlen(str); ++i){
        if (isOpeningBracket(str[i]) != -1){
            insertToFront(&stack, str[i]);
            continue;
        }
        if (!stack) return false;
        if (isOpeningBracket(stack -> val) != isClosingBracket(str[i])) return false;
        deleteAtFront(&stack);
    }
    return stack == NULL;
}
int main(){
    char str[STR_LEN];
    scanf("%s", str);
    printf("%d", validParentheses(str));
}