#include<stdio.h>
#include<stdlib.h>
int topSignal(int *arr, int n){
    int res = 0;
    for (int i = 1; i < n - 1; ++i){
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) ++res;
    }
    return res;
}
int main(){
    int n;
    scanf("%d", &n);
    int *arr = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
    printf("%d", topSignal(arr, n));
    return 0;
}