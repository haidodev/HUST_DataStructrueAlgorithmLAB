#include<stdio.h>
#include<stdlib.h>
int main(){

    int n, *arr;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    arr = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        printf("Enter arr[%d]: ", i);
        scanf("%d", arr + i);
    }
    int sum = 0;
    for (int i = 0; i < n; ++i){
        sum += arr[i];
        printf("%d ", arr[i]);
    }
    printf("\nSum = %d\n", sum);
}