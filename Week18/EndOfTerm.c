#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define CLASS_CODE 10
#define COURSE_CODE 10
#define SCHEDULE 20
#define FILENAME "Schedule.txt"
typedef struct l_node {
    char class_code[CLASS_CODE], course_code[COURSE_CODE], schedule[SCHEDULE];
    struct l_node *next;
} LinkedList;
typedef struct course_node {
    char course_code[COURSE_CODE];
    int count_class;
    struct course_node *next;
}CLinkedList;
CLinkedList *CLLMakeNode(char *course_code){
    CLinkedList *newNode = (CLinkedList*)malloc(sizeof(CLinkedList));
    strcpy(newNode -> course_code, course_code);
    newNode -> count_class = 1;
    newNode -> next = NULL;
}
void printCLLNode(CLinkedList *head){
    printf("%15s%7s\n", "COURSE CODE", "COUNT");
    while (head){
        printf("%15s%7d\n", head -> course_code, head -> count_class);
        head = head -> next;
    }
    
}
void CLLAppendAtBack(CLinkedList **head, CLinkedList **tail, CLinkedList *newNode){
    if (*tail){
        (*tail) -> next = newNode;
    }
    *tail = newNode;
    if (!(*head)) *head = *tail;
}
CLinkedList* CLLFindNode(CLinkedList *head, char *course_code){
    if (!head) return NULL;
    if (strcmp(head -> course_code, course_code) != 0) return CLLFindNode(head -> next, course_code);
    return head;
}
void showMenu(){
    printf("\n*************************\n");
    printf("TIME TIMETABLE\n");
    printf("1. Read file\n");
    printf("2. Traverse the list\n");
    printf("3. Search classes\n");
    printf("4. Delete class\n");
    printf("5. Order classes\n");
    printf("6. Count classes\n");
    printf("7. Quit\n");
}
LinkedList *makeNode(char *class_code, char *course_code, char *schedule){
    LinkedList *newNode = (LinkedList*)malloc(sizeof(LinkedList));
    strcpy(newNode -> class_code, class_code);
    strcpy(newNode -> course_code, course_code);
    strcpy(newNode -> schedule, schedule);
    newNode -> next = NULL;
    return newNode;
}
void appendAtBack(LinkedList **head, LinkedList **tail, LinkedList *newNode){
    if (*tail){
        (*tail) -> next = newNode;
    }
    *tail = newNode;
    if (!(*head)) *head = *tail;
}
bool deleteNode(LinkedList **head, LinkedList **tail, char *class_code){
    if (!(*head)) return false;
    if (strcmp((*head) -> class_code, class_code) == 0){
        LinkedList *tmpNode = *head;
        *head = (*head) -> next;
        free(tmpNode);
        return true;
    }
    LinkedList *curNode = *head;
    while (curNode -> next && strcmp(curNode -> next -> class_code, class_code) != 0) curNode = curNode -> next;
    if (!(curNode -> next)) return false;
    if (strcmp((*tail) -> class_code, class_code) == 0){
        LinkedList *tmpNode = *tail;
        *tail = curNode;
        (*tail) -> next = NULL;
        free(tmpNode);
        return true;
    }
    LinkedList *tmpNode = curNode -> next;
    curNode -> next = tmpNode -> next;
    free(tmpNode);
    return true;
    
}
void removeNewLine(char *str){
    int len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = 0;
}
void ReadFile(LinkedList **head, LinkedList **tail){
    FILE *fi = fopen(FILENAME, "r");
    if (!fi){
        printf("Cannot open file %s\n", FILENAME);
        return;
    }
    char class_code[CLASS_CODE], course_code[COURSE_CODE], schedule[SCHEDULE];
    while (fgets(class_code, sizeof(class_code), fi) != NULL){
        fgets(course_code, sizeof(course_code), fi);
        fgets(schedule, sizeof(schedule), fi);
        removeNewLine(class_code);
        removeNewLine(course_code);
        removeNewLine(schedule);
        appendAtBack(head, tail, makeNode(class_code, course_code, schedule));
    }
}
void printNode(LinkedList *node){
    printf("%15s%15s%30s\n", node -> class_code, node -> course_code, node -> schedule);
}
void TraverseList(LinkedList *head){
    printf("%15s%15s%30s\n", "CLASS CODE", "COURSE CODE", "SCHEDULE");
    while (head){
        printNode(head);
        head = head -> next;
    }
}
void SearchClass(LinkedList *head){
    char course_code[COURSE_CODE];
    printf("Enter the cource code: ");
    scanf("%s", course_code);
    printf("%15s%15s%30s\n", "CLASS CODE", "COURSE CODE", "SCHEDULE");
    bool found = false;
    while (head){
        if (strcmp(course_code, head -> course_code) == 0){
            found = true;
            printNode(head);
        }
        head = head -> next;
    }
    if (!found) printf("Course code: %s not found!\n", course_code);
}
void DeleteClass(LinkedList **head, LinkedList **tail){
    char class_code[COURSE_CODE];
    printf("Enter the class code: ");
    scanf("%s", class_code);
    if (deleteNode(head, tail, class_code))
        printf("Remove class: %s successfully!\n", class_code);
    else
        printf("Failed to remove class: %s!\n", class_code);

    TraverseList(*head);
}
void OrderClass(LinkedList **head, LinkedList **tail){
    LinkedList *newHead = NULL, *newTail = NULL;
    while (*head){
        LinkedList *tmpNode = *head, *minNode = *head;
        while (tmpNode){

            if (strcmp(tmpNode -> class_code, minNode -> class_code) < 0) {
                minNode = tmpNode;
            }
            tmpNode = tmpNode -> next;
            
        }
        appendAtBack(&newHead, &newTail, makeNode(minNode -> class_code, minNode -> course_code, minNode -> schedule));
        deleteNode(head, tail, minNode -> class_code);
    }
    TraverseList(newHead);
    *head = newHead;
    *tail = newTail;
}
void CountClass(LinkedList *head){
    CLinkedList *chead = NULL, *ctail = NULL;
    while (head){
        char course_code[COURSE_CODE];
        strcpy(course_code ,head -> course_code);
        CLinkedList *curNode = CLLFindNode(chead, course_code);
        if (!curNode) {
            curNode = CLLMakeNode(course_code);
            CLLAppendAtBack(&chead, &ctail, curNode);
        } else {
            curNode -> count_class += 1;
        }
        head = head -> next;
    }
    printCLLNode(chead);
}
void doCommand(){
    int choice;
    LinkedList *head = NULL, *tail = NULL;
    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ReadFile(&head, &tail);
            break;
        case 2: 
            TraverseList(head);
            break;
        case 3:
            SearchClass(head);
            break;
        case 4:
            DeleteClass(&head, &tail);
            break;
        case 5:
            OrderClass(&head, &tail);
            break;
        case 6:
            CountClass(head);
            break;
        case 7:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }

    } while (choice != 7);
    

}
int main(){
    doCommand();
}
