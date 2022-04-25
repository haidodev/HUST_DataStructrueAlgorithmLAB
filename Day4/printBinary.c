#include<stdio.h>
#include<stdlib.h>
void printBinary(char prev, char *arr, int curIndex, int n){
    if (curIndex == n) {
        for (int i = 0; i < n; ++i) printf("%c", arr[i]);
        printf("\n");
        return;
    }
    arr[curIndex] = '0';
    printBinary(arr[curIndex], arr, curIndex + 1, n);
    if (prev == '0'){
        arr[curIndex] = '1';
        printBinary(arr[curIndex], arr, curIndex + 1, n);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    char *arr;
    arr = (char *)calloc(n, sizeof(char));
    printBinary('0', arr, 0, n);
}