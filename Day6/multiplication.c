#include<stdio.h>
#include<stdlib.h>
int XORCalc(int* arr, int arr_sz){
    int res = arr[0];
    for (int i = 1; i < arr_sz; ++i) res ^= arr[i];
    return res;
}
int multiplication(int *a, int *b, int *c, int a_base, int b_base){
    for (int i = 0; i <= a_base; ++i){
        for (int j = 0; j <= b_base; ++j){
            c[i + j] += a[i] * b[j];
        }
    }
}
void showArr(int *arr, int arr_sz){
    for (int i = 0; i < arr_sz; ++i) printf("%d ", arr[i]);
    printf("\n");
}
int main(){
    int m;
    scanf("%d", &m);
    int *a = (int*)calloc(m + 1, sizeof(int));
    for (int i = 0; i <= m; ++i){
        scanf("%d", &a[i]);
    }
    int n;
    scanf("%d", &n);
    int *b = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; ++i){
        scanf("%d", &b[i]);
    }
    int *c = (int*)calloc(m + n + 1, sizeof(int));
    multiplication(a, b, c, m, n);
    printf("m = %d n = %d \n", m, n);
    showArr(a, m + 1);
    showArr(b, n + 1);
    showArr(c, m + n + 1);
    printf("%d", XORCalc(c, m + n + 1));
}