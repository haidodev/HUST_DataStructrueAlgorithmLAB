#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#define MAX_LEN 50
void showAnswer(int *res, char *ip){
    int index = 0;
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < res[i]; ++j){
            printf("%c", ip[index++]);
        }
        if (i < 3) printf(".");
    }
    printf("\n");
}
void generateIPAddress(int curPos, int curVal, int curGrp, int *res, char *ip){
    if (curPos == strlen(ip) && res[3] != 0){
        showAnswer(res, ip);
    }
    if (curVal > 0 || res[curGrp] == 0){
        curVal = curVal * 10 + (ip[curPos] - '0');
        if (curVal > 0 && curVal < 256){
                ++res[curGrp];
                generateIPAddress(curPos + 1, curVal, curGrp, res, ip);
                --res[curGrp];
            } 
    }
    
    if (res[curGrp] && curGrp < 3){
        ++curGrp;
        res[curGrp] = 1;
        generateIPAddress(curPos + 1, ip[curPos] - '0', curGrp, res, ip);
        res[curGrp] = 0;
    }
    
}
bool validIpAddress(int *res, char *ip) {
    int index = 0;
    for (int i = 0; i < 4; ++i){
        if (ip[index] == '0' && res[i] > 1) return false;
        int val = 0;
        for (int j = 0; j < res[i]; ++j){
            val = val * 10 + ip[index++] - '0';
        }
        if (val >= 256) return false;
    }
    return true;
}
void generateIPAddress2(int digLeft, int curGrp, int *res, char *ip){
    if (curGrp == 3){
        res[curGrp] = digLeft;
        if (validIpAddress(res, ip)){
            showAnswer(res, ip);
        }
        return;
    }
    for (int i = 1; i < 4; ++i){
        if (digLeft > i) {
            res[curGrp] = i;
            generateIPAddress2(digLeft - i, curGrp + 1, res, ip);
        }
    }
}
int main(){
    char ip[MAX_LEN];
    printf("IP String: ");
    fgets(ip, MAX_LEN, stdin);
    if (ip[strlen(ip) - 1] == '\n') ip[strlen(ip) - 1] = 0;
    int res[] = {0, 0, 0, 0};
    printf("All valid IP Address: \n");
    generateIPAddress(0, 0, 0, res, ip);
    printf("All valid IP Address: \n");
    int res2[] = {0, 0, 0, 0};
    generateIPAddress2(strlen(ip), 0, res2, ip);
}