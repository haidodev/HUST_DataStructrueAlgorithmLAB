#include<stdio.h>
#include<string.h>
#define MAX_DIG 100000
void reverseString(char *str){
    for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j){
        int tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}
void multipleBigWSmall(char *a, int b, char *res){
    int prev = 0, index = 0;
    for (int i = strlen(a) - 1; i >= 0; --i){
        int cur = a[i] - '0';
        cur = cur * b + prev;
        prev = cur / 10;
        res[index++] = cur % 10 + '0';
    }
    if (prev) res[index++] = prev + '0';
    res[index] = 0;

    reverseString(res);
}
void addBigWBig(char *a, char *b, char *res){
    int ia = strlen(a) - 1, ib = strlen(b) - 1, ires = 0;
    int prev = 0;
    while (ia >= 0 && ib >= 0){
        int cura = a[ia] - '0', curb = b[ib] - '0';
        int cur = cura + curb + prev;
        prev = cur / 10;
        res[ires++] = cur % 10 + '0';
        --ia; --ib;
    }
    while (ia >= 0){
        int cura = a[ia] - '0';
        int cur = cura + prev;
        prev = cur / 10;
        res[ires++] = cur % 10 + '0';
        --ia;
    }
    while (ib >= 0){
        int curb = b[ib] - '0';
        int cur = curb + prev;
        prev = cur / 10;
        res[ires++] = cur % 10 + '0';
        --ib;
    }
    if (prev) res[ires++] = prev + '0';
    res[ires] = 0;
    reverseString(res);
}
void addTraillingZeros(char *res, int num){
    int ires = strlen(res);
    while (num--){
        res[ires++] = '0';
    }
    res[ires] = 0;
}
void multiplyBigWBig(char *a, char *b, char *res){
    for (int i = strlen(b) - 1; i >= 0; --i){
        char multiple[MAX_DIG];
        multipleBigWSmall(a, b[i] - '0', multiple);
        addTraillingZeros(multiple, strlen(b) - i - 1);
        char tmp[MAX_DIG];
        strcpy(tmp, res);
        addBigWBig(multiple, tmp, res);
    }
}
void removeNewLine(char *str){
    int lastIndex = strlen(str) - 1;
    if (str[lastIndex] == '\n') str[lastIndex] = 0;
}
int main(){
    char a[MAX_DIG], b[MAX_DIG], res[MAX_DIG];
    fgets(a, MAX_DIG, stdin);
    removeNewLine(a);
    fgets(b, MAX_DIG, stdin);
    removeNewLine(b);
    multiplyBigWBig(a, b, res);
    printf("%s", res);
}