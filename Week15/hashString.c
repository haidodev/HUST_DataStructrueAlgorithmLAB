#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 256
int arr[200];
int hashString(char *str, int m){
    int len = strlen(str), res = 0;
    for (int i = 0; i < len; ++i){
        long long int tmp = arr[len - i - 1] * str[i];
        res = (tmp + res) % m;
    }
    return res;
}
int main(){
    int testcase, m;
    scanf("%d %d", &testcase, &m);
    arr[0] = 1;
    for (int i = 1; i < 200; ++i){
        long long int tmp = arr[i - 1];
        tmp *= 256;
        arr[i] = tmp % m;
    }
    while (testcase--){
        char str[MAX_LEN];
        scanf("%s", str);
        printf("%d\n", hashString(str, m));
    }
    return 0;
}