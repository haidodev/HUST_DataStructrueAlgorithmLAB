#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 256
#define DIGITS 10
typedef struct t_node
{
    int phone_call, time_call;
    bool isLastNode;
    struct t_node *nextdig[DIGITS];
} trie;
void addToPhoneNumber(trie *root, char *phoneNumber, int value)
{
    if (strlen(phoneNumber) == 0)
    {
        root->isLastNode = true;
        ++root->phone_call;
        root->time_call += value;
        return;
    }
    int nextDigit = phoneNumber[0] - '0';
    trie *nextRoot = (root->nextdig)[nextDigit];
    if (!nextRoot)
    {
        nextRoot = (trie *)malloc(sizeof(trie));
        root -> isLastNode = false;
        root -> phone_call = 0;
        root -> time_call = 0;
        (root->nextdig)[nextDigit] = nextRoot;
    }
    addToPhoneNumber(nextRoot, phoneNumber + 1, value);
}

int callLength(char *time_begin, char *time_end)
{
    int h1, h2, m1, m2, s1, s2;
    sscanf(time_begin, "%d:%d:%d", &h1, &m1, &s1);
    sscanf(time_end, "%d:%d:%d", &h2, &m2, &s2);
    return (h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1);
}
trie* findPhoneNumber(trie *root, char *phoneNumber){
    if (!root) return NULL;
    if (strlen(phoneNumber) == 0) return root -> isLastNode ? root : NULL;
    int nextDigit = phoneNumber[0] - '0';
    trie *nextRoot = (root->nextdig)[nextDigit];
    return findPhoneNumber(nextRoot, phoneNumber + 1); 
}
bool validPhoneNumber(char *phoneNumber){
    if (strlen(phoneNumber) != 10) return false;
    for (int i = 0; i < 10; ++i){
        if (phoneNumber[i] > '9' || phoneNumber[i] < '0') return false;
    }
    return true;
}
void doCommand(){
    FILE *fi = fopen("FILENAME.INP", "r");
    fi = stdin;
    bool allValidPhoneNumber = true;
    int totalCalls = 0;
    trie *root = (trie *)malloc(sizeof(trie));
    char command[MAXLEN];
    while (fscanf(fi, "%s", command) && strcmp(command, "#") != 0){
        ++totalCalls;
        char src[MAXLEN], dest[MAXLEN], day[MAXLEN], time_begin[MAXLEN], time_end[MAXLEN];
        fscanf(fi, "%s %s %s %s %s", src, dest, day, time_begin, time_end);
        //printf("%s %s %s %s %s %d \n", src, dest, day, time_begin, time_end, callLength(time_begin, time_end));
        if (!validPhoneNumber(src) || !validPhoneNumber(dest)){
            allValidPhoneNumber = false;
            continue;
        }
        addToPhoneNumber(root, src, callLength(time_begin, time_end));

    }
    while (fscanf(fi, "%s", command) && strcmp(command, "#") != 0){
        if (strcmp(command, "?check_phone_number") == 0){
            printf("%d\n", allValidPhoneNumber ? 1 : 0);
        }
        if (strcmp(command, "?number_calls_from") == 0){
            char phoneNumber[MAXLEN];
            fscanf(fi, "%s", phoneNumber);
            trie* curNode = findPhoneNumber(root, phoneNumber);
            printf("%d\n", curNode ? curNode -> phone_call : 0);
        }
        if (strcmp(command, "?number_total_calls") == 0){
            printf("%d\n", totalCalls);
        }
        if (strcmp(command, "?count_time_calls_from") == 0){
            char phoneNumber[MAXLEN];
            fscanf(fi, "%s", phoneNumber);
            trie* curNode = findPhoneNumber(root, phoneNumber);
            printf("%d\n", curNode ? curNode -> time_call : 0);        
        }
    }

}
int main()
{
    doCommand();
}