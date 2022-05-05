#include<stdio.h>
#include<stdlib.h>
#define max(a, b) (a) > (b) ? (a) : (b)
int longestConsecutiveIncrease(int *arr, int arr_sz){
    int prev = 0, curLen = 0, res = 1;
    for (int i = 0; i < arr_sz; ++i){
        if (arr[i] > prev) ++curLen;
        else {
            res = max(res, curLen);
            curLen = 1;
        }
        prev = arr[i];
    }
    return max(res, curLen);
}
int main(){
    int n, *arr;
    scanf("%d", &n);
    arr =(int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
    printf("%d", longestConsecutiveIncrease(arr, n));
}