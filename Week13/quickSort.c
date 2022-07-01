#include<stdio.h>
#include<stdlib.h>
void printArray(int *arr, int left, int right){
    for (int i = left; i <= right; ++i) printf("%d ", arr[i]);
    printf("\n"); 
}
void buildArray(int **arr, int *n){
    scanf("%d", n);
    int numElm = *n;
    *arr = (int*)calloc(numElm, sizeof(int));
    for (int i = 0; i < numElm; ++i){
        scanf("%d", &(*arr)[i]);
    }
}
void swap(int *a, int *b){
    int tmp  = *a;
    *a = *b;
    *b = tmp;
}
int partition(int *arr, int left, int right){
    int index = left - 1;
    while (left < right){
        if (arr[left] <= arr[right]){
            ++index;
            if (index != left) swap(&arr[index], &arr[left]);
        } 
        ++left;
    }
    swap(&arr[index + 1], &arr[right]);
    return index + 1;
}
int myPartition(int *arr, int left, int right){
    int midIndex = left;
    int l = left, r = right;
    for (int i = left; i < right; ++i) if (arr[i] <= arr[right]) ++midIndex;
    swap(&arr[midIndex], &arr[right]);
    while (left < midIndex && right > midIndex){
        while (left < midIndex && arr[left] <= arr[midIndex]) ++left;
        while (right > midIndex && arr[right] > arr[midIndex]) --right;
        if (left < midIndex && right > midIndex) swap(&arr[left], &arr[right]);
    }
    //printArray(arr, l, r);
    return midIndex;
}
void quickSort(int *arr, int left, int right) {
    if (left >= right) return;
    int midIndex = myPartition(arr, left, right);
    quickSort(arr, left, midIndex - 1);
    quickSort(arr, midIndex + 1, right);
}   

int main(){
    int *arr, n;
    buildArray(&arr, &n);
    quickSort(arr, 0, n - 1);
    printArray(arr, 0, n - 1);
}