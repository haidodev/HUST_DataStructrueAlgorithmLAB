#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 256
#define MAXELM 50
typedef struct
{
    char name[MAXLEN], email[MAXLEN];
} studentProfile;
struct node
{
    studentProfile profile;
    struct node *next;
};
typedef struct node LinkedList;
void printMenu();
bool runProgram();
void readString(char *str, char *command);
void executeLoad(LinkedList **head, LinkedList **tail);
void executeAdd(LinkedList **head, LinkedList **tail);
void executeStore(LinkedList *head);
void appendLast(LinkedList **head, LinkedList **tail, studentProfile newProfile);
void readNode(LinkedList *head, studentProfile *newProfile);
bool checkFileOpenable(char *filename);
int main()
{
    while (runProgram());
    return 0;
}
bool runProgram()
{
    void printMenu();
}
bool checkFileOpenable(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL){
        return false;
    }
    fclose(fp);
    return true;
}
void readString(char *str, char *command)
{
    fgets(str, MAXLEN, stdin);
    int lastIndex = strlen(str) - 1;
    if (str[lastIndex] == '\n')
        str[lastIndex] = 0;
}
void appendLast(LinkedList **head, LinkedList **tail, studentProfile newProfile){
    LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    strcpy((newNode -> profile).name, newProfile.name);
    strcpy((newNode -> profile).email, newProfile.email);
    if (!(*tail)) {
        *head = newNode;
        *tail = newNode;
        return;
    }
    (*tail) -> next = newNode;
    *tail = newNode;
}

void executeLoad(LinkedList **head, LinkedList **tail)
{
    char filename[MAXLEN];
    readString(filename);
    if (!checkFileOpenable(filename)) {
        printf("Cannot open file!");
        return;
    }
    FILE *fp = fopen(filename, "rb");
    studentProfile profile;
    while (true){
        int sz = fread(&profile, sizeof(studentProfile), 1, fp);
        if (sz == 0) break;
        appendLast(head, tail, profile);
    }
    fclose(fp);

}
void executeAdd(LinkedList **head, LinkedList **tail){
    studentProfile newProfile;
    readString(newProfile.name, , "Enter file name: ");
    readString(newProfile.email);
    appendLast(head, last, newProfile);

}
void readNode(LinkedList *head, studentProfile *newProfile){
    strcpy(newProfile -> name, (head -> profile).name);
    strcpy(newProfile -> email, (head -> profile).email);
}
void executeStore(LinkedList *head){
    char filename[MAXLEN];
    readString(filename, "Enter file name: ");
    FILE *fp = fopen(filename, "wb");
    studentProfile profile;
    while (!head){
        readNode(head, &profile);
        fwrite(&profile, sizeof(studentProfile), 1, fp);
        head = head -> next;
    }
    fclose(fp);
}
void printMenu()
{
    printf("ALL COMMANDS\n");
    printf("1. Load data from file\n");
    printf("2. Print the information loaded\n");
    printf("3. Add a new profile\n");
    printf("4. Remove a profile\n");
    printf("5. Find a profile\n");
    printf("6. Store into external file\n");
    printf("7. Quit\n");
}