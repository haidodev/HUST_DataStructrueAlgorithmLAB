#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 256
#define FILENAME "INPUT.INP"
#define ACCOUNT_LEN 21
#define ATM_LEN 11
typedef struct t_node {
    char account_number[ACCOUNT_LEN];
    int money;
    struct t_node *left, *right;
} AccountData;
AccountData *BTMakeNode(char *account_number, int nodeMoney){
    AccountData *newNode = (AccountData *)malloc(sizeof(AccountData));
    strcpy(newNode -> account_number, account_number);
    newNode -> money = nodeMoney;
    return newNode;
}
AccountData *BTFindNode(AccountData *root, char *account_number){
    if (!root) return NULL;
    if (strcmp(root -> account_number, account_number) == 0) return root;
    if (strcmp(account_number, root -> account_number) > 0) return BTFindNode(root -> right, account_number);
    return BTFindNode(root -> left, account_number);
}
void BTAppendChild(AccountData **root, AccountData *newNode){
    if (!(*root)){
        *root = newNode;
        return;
    }
    AccountData *curNode = *root;
    if (strcmp(newNode -> account_number, curNode -> account_number) > 0){
        BTAppendChild(&((*root) -> right), newNode);
        return;
    }
    BTAppendChild(&((*root) -> left), newNode);
    
}
void BTInorder(AccountData *root){
    if (!root) return;
    BTInorder(root -> left);
    printf("%s ", root -> account_number);
    BTInorder(root -> right);
}
void doCommand(){
    FILE *fi = fopen(FILENAME, "r");
    // if (!fi){
    //     printf("Cannot open file to read!\n");
    //     return;
    // }
    fi = stdin;
    bool allmoneyidPhoneNumber = true;
    int totalTransactions = 0, totalMoneyTransactions = 0;
    AccountData *root = NULL;
    char command[MAXLEN];
    while (fscanf(fi, "%s", command) && strcmp(command, "#") != 0){
        char src[MAXLEN], dest[MAXLEN], time[MAXLEN], atm[MAXLEN];
        int amount;
        strcpy(src, command);
        fscanf(fi, "%s %d %s %s", dest, &amount, time, atm);
        //printf("%s %s %d %s %s\n", src, dest, amount, time, atm);
        
        AccountData *curAcc = BTFindNode(root, src);
        if (curAcc) curAcc -> money += amount;
        else {
            BTAppendChild(&root, BTMakeNode(src, amount));
        }
        curAcc = BTFindNode(root, dest);
        if (!curAcc) {
            BTAppendChild(&root, BTMakeNode(dest, 0));
        }
        ++totalTransactions;
        totalMoneyTransactions += amount;
    }
    while (fscanf(fi, "%s", command) && strcmp(command, "#") != 0){
        if (strcmp(command, "?number_transactions") == 0){
            printf("%d\n", totalTransactions);
        }
        if (strcmp(command, "?total_money_transaction") == 0){
            printf("%d\n", totalMoneyTransactions);
        }
        if (strcmp(command, "?list_sorted_accounts") == 0){
            BTInorder(root);
            printf("\n");
        }
        if (strcmp(command, "?total_money_transaction_from") == 0){
            char account[MAXLEN];
            fscanf(fi, "%s", account);
            AccountData* curNode = BTFindNode(root, account);
            printf("%d\n", curNode ? curNode -> money : 0);        
        }
        if (strcmp(command, "?inspect_cycle") == 0){
            char account[MAXLEN];
            fscanf(fi, "%s", account);
            AccountData* curNode = BTFindNode(root, account);
            printf("STILL BUILDING");
        }
    }

}
int main()
{
    doCommand();
}