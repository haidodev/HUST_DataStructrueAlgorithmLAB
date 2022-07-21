#include<stdio.h>
#include<stdlib.h>
#define MAX(a, b) (a) > (b) ? (a) : (b)
void swapArr(int *arr1, int *arr2, int arr_sz){
    for (int i = 0; i < arr_sz; ++i){
        int tmp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = tmp;
    }
}
void sortInterval(int **arr, int arr_sz){
    for (int i = 0; i < arr_sz; ++i){
        int minIndex = i;
        for (int j = i + 1; j < arr_sz; ++j){
            if (arr[j][1] < arr[minIndex][1]) minIndex = j;
        }
        swapArr(arr[i], arr[minIndex], 3);
    }
}
int main(){
    int n, **arr;
    scanf("%d", &n);
    arr = (int **)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i){
        arr[i] = (int*)calloc(3, sizeof(int));
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
    sortInterval(arr, n);
    
    int *dp = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        dp[i] = arr[i][2];
        for (int j = i - 1; j >= 0; --j){
            if (arr[i][0] > arr[j][1]) dp[i] = MAX(dp[i], dp[j] + arr[i][2]);
            else dp[i] = MAX(dp[i], dp[j]);
        }
    }
        printf("%d", dp[n - 1]);

}