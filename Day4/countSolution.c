#include<stdio.h>
#include<stdlib.h>
void readInput(int *n, int *arr, int *M){
    scanf("%d", n);
    arr = (int *)calloc(*n, sizeof(int));
    for (int i = 0; i < *n; ++i){
        scanf("%d", arr + i);
    }
    scanf("%d", M);
    
}
int countSolution(int cur, int *arr, int n, int M){
    if (cur == n - 1) return (M % arr[cur]) == 0;
    int res = 0;
    for (int i = 1; M > 0; ++i){
        M -= arr[cur];
        if (M > 0) res += countSolution(cur + 1, arr, n, M);
        printf("%d %d\n", cur, res);
    }
    return res;
}
int main(){
    int n, *arr, M;
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        scanf("%d", arr + i);
    }
    scanf("%d", &M);
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("%d\n", countSolution(0, arr, n, M));
}