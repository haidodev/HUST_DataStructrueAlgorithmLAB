#include<stdio.h>
#include<stdlib.h>
int count = 0;
void showChessBoard(char ** board, int n){
    for (int i = 0; i < n; ++i){
        printf("%s\n", board[i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i){
        printf("-");
    }
    printf("COUNT = %d\n", ++count);

}
void maskCell(int n, int i, int j, int* col, int* leftDiag, int* rightDiag, char ** board){
    int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    col[j] = 1;
    leftDiag[leftDiagIndex] = 1;
    rightDiag[rightDiagIndex] = 1;
    board[i][j] = 'Q';
}
void unMaskCell(int n, int i, int j, int* col, int* leftDiag, int* rightDiag, char ** board){
    int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    col[j] = 0;
    leftDiag[leftDiagIndex] = 0;
    rightDiag[rightDiagIndex] = 0;
    board[i][j] = '.';
}
void generateNthQueen(int n, int i, int* col, int* leftDiag, int* rightDiag, char ** board){
    
    if (i == n){
        showChessBoard(board, n);
        return;
    }
    for (int j = 0; j < n; ++j){
        int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
        //printf("row: %d, col: %d, rightDiag: %d, leftDiag: %d\n", i, j, rightDiagIndex, leftDiagIndex);
        if (col[j] == 0 && leftDiag[leftDiagIndex] == 0 && rightDiag[rightDiagIndex] == 0){
        //printf("---i: %d, col: %d, rightDiag: %d, leftDiag: %d\n", i, j, rightDiagIndex, leftDiagIndex);
            
            maskCell(n, i, j, col, leftDiag, rightDiag, board);
            generateNthQueen(n, i + 1, col, leftDiag, rightDiag, board);
            unMaskCell(n, i, j, col, leftDiag, rightDiag, board);
        }
    }
}
int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    char **board = (char **)calloc(n, sizeof(char*));
    for (int i = 0; i < n; ++i){
        board[i] = (char *)calloc(n, sizeof(char));
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            board[i][j] = '.';
        }
    }
    int *col = (int*)calloc(n, sizeof(int)), *leftDiag = (int*)calloc(2 * n - 1, sizeof(int)), *rightDiag = (int*)calloc(2 * n - 1, sizeof(int));
    generateNthQueen(n, 0, col, leftDiag, rightDiag, board);
}
