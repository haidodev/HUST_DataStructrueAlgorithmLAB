#include<stdio.h>
#include<stdlib.h>
void showChessBoard(int *col, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (col[j] == i + 1) printf("Q");
            else printf(".");
        }
        printf("\n");
    }
    for (int i = 0; i < n; ++i){
        printf("-");
    }
    printf("\n");

}
void maskCell(int n, int i, int j, int* col, int* leftDiag, int* rightDiag){
    int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    col[j] = i + 1;
    leftDiag[leftDiagIndex] = 1;
    rightDiag[rightDiagIndex] = 1;
}
void unMaskCell(int n, int i, int j, int* col, int* leftDiag, int* rightDiag){
    int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    col[j] = 0;
    leftDiag[leftDiagIndex] = 0;
    rightDiag[rightDiagIndex] = 0;
}
void generateNthQueen(int n, int i, int* col, int* leftDiag, int* rightDiag){
    
    if (i == n){
        showChessBoard(col, n);
        return;
    }
    for (int j = 0; j < n; ++j){
        int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
        if (col[j] == 0 && leftDiag[leftDiagIndex] == 0 && rightDiag[rightDiagIndex] == 0){
            //printf("%d, %d, %d", )
            maskCell(n, i, j, col, leftDiag, rightDiag);
            generateNthQueen(n, i + 1, col, leftDiag, rightDiag);
            unMaskCell(n, i, j, col, leftDiag, rightDiag);
        }
    }
}
int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int *col = (int*)calloc(n, sizeof(int)), *leftDiag = (int*)calloc(2 * n - 1, sizeof(int)), *rightDiag = (int*)calloc(2 * n - 1, sizeof(int));
    generateNthQueen(n, 0, col, leftDiag, rightDiag);
}
