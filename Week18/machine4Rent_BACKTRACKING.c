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
int maxRevenue(int prev, int n, int **arr){
    int res = 0, minStartTime = (prev == -1 ? 0 : arr[prev][1]);
    for (int i = prev + 1; i < n; ++i){
        if (arr[i][0] > minStartTime){
            int revenue = maxRevenue(i, n, arr) + arr[i][2];

            res = MAX(res, revenue);
        }
    }
    return res;
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
    printf("%d", maxRevenue(-1, n, arr));
}

/*
2 4 5 8 10 12 13 14 18 19 30 34 
2 3 5 7 8 9 12 13 18 20 
1 3 3 3 7 9 9  11 11 13
1 1 2 3 4 4 5  6  7  8
2 2 4 4 8 8 10 12 12 14 
*/