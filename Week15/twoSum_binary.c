#include<stdio.h>
#include<stdlib.h>
void mergeArray(int *arr, int left, int mid, int right){
    int *tmp = (int*) malloc((right - left  + 1) * sizeof(int)), curIdx = -1;
    for (int i = left, j = mid + 1; i <= mid || j <= right;){
        ++curIdx;
        if (i == mid + 1){
            tmp[curIdx] = arr[j++];
            continue;
        }
        if (j == right + 1){
            tmp[curIdx] = arr[i++];
            continue;
        }
        if (arr[i] < arr[j]) tmp[curIdx] = arr[i++];
        else tmp[curIdx] = arr[j++];
    }
    for (int i = 0; i <= curIdx; ++i){
        arr[i + left] = tmp[i];
    }
    free(tmp);
}
void mergeSort(int *arr, int left, int right){
    if (left == right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    mergeArray(arr, left, mid, right);
}
int binarySearch(int *arr, int left, int right, int val){
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] < val) left = mid + 1;
        else right = mid;
    }
    return arr[left] ==  val ? left : -1;
    
}
int sumPair(int *arr, int arr_sz, int s){
    int res = 0;
    for (int i = 0; i < arr_sz - 1; ++i){
        if (binarySearch(arr, i + 1, arr_sz - 1, s - arr[i]) != -1) ++res;
    }
    return res;
}
int main(){
    int *arr, n, s;
    FILE *fi = stdin;
    fscanf(fi, "%d %d", &n, &s);
    arr = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        fscanf(fi, "%d", &arr[i]);
    }
    fclose(fi);
    mergeSort(arr, 0, n - 1);
    printf("%d", sumPair(arr, n, s));
}