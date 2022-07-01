#include<stdio.h>
int evaluatedValue(int *arr){
    int num1 = arr[0] * 100 + arr[1] * 10 + arr[2];
    int num2 = arr[3] * 100 + 62;
    int num3 = arr[4] * 1000 + arr[5] * 100 + arr[6]*10 + arr[2];
    return num1 - num2 + num3;
}
void printArray(int *arr){
    for (int i = 0; i < 7; ++i) printf("%d ", arr[i]);
    printf("\n");
}
void backtracking(int n, int *arr, int *used, int charFilled, int *cnt){
    if (charFilled == 7){
        if (evaluatedValue(arr) == n) {
            (*cnt) += 1;
        }
        return;
    }
    for (int i = 1; i <= 9; ++i){
        if (used[i]) continue;
            used[i] = 1;
            arr[charFilled] = i;
            backtracking(n, arr, used, charFilled + 1, cnt);
            used[i] = 0;
        
    }
}
int main(){
    int n;
    scanf("%d", &n);
    int arr[7] = {0}, cnt = 0, used[10] = {0, 0, 0, 0, 0, 0, 0};
    backtracking(n, arr, used, 0, &cnt);
    printf("%d", cnt);
    return 0;

}