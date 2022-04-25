#include<stdio.h>
#include<stdlib.h>
void printPermutation(int numLeft, int *arr, int arr_sz, int *mask){
    if (numLeft == 0){
        for (int i = 0; i < arr_sz; ++i) printf("%d ", arr[i] + 1);
        printf("\n");
        return ; 
    }
    for (int i = 0; i < arr_sz; ++i){
        if (!mask[i]) {
            mask[i] = 1;
            arr[arr_sz - numLeft] = i;
            printPermutation(numLeft - 1, arr, arr_sz, mask);
            mask[i] = 0;
        }
    }
}
int main(){
    int n;
    scanf("%d", &n);
    int *mask = (int *)calloc(n, sizeof(int)), *arr = (int *)calloc(n, sizeof(int));
    printPermutation(n, arr, n, mask);
}