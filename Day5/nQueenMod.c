#include<stdio.h>
#include<stdlib.h>
void showChessBoard(char ** board, int n){
    for (int i = 0; i < n; ++i){
        printf("%s\n", board[i]);
    }
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
void generateNthQueen(int n, int i, int* row, int* col, int* leftDiag, int* rightDiag, char ** board){
    
    if (i == n){
        showChessBoard(board, n);
        return;
    }
    if (row[i] == 1) generateNthQueen(n, i + 1, row, col, leftDiag, rightDiag, board);
    for (int j = 0; j < n; ++j){
        int  rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
        //printf("row: %d, col: %d, rightDiag: %d, leftDiag: %d\n", i, j, rightDiagIndex, leftDiagIndex);
        if (col[j] == 0 && leftDiag[leftDiagIndex] == 0 && rightDiag[rightDiagIndex] == 0){
        //printf("---i: %d, col: %d, rightDiag: %d, leftDiag: %d\n", i, j, rightDiagIndex, leftDiagIndex);
            
            maskCell(n, i, j, col, leftDiag, rightDiag, board);
            generateNthQueen(n, i + 1, row, col, leftDiag, rightDiag, board);
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
    int *col = (int*)calloc(n, sizeof(int)), *row = (int*)calloc(n, sizeof(int)), *leftDiag = (int*)calloc(2 * n - 1, sizeof(int)), *rightDiag = (int*)calloc(2 * n - 1, sizeof(int));
    int prevQueen = 0;
    printf("%d", &prevQueen);
    while (prevQueen--){
        int r, c;
        printf("%d", &r);
        printf("%d", &c);
        row[r] = 1;
        maskCell(n, r, c, col, leftDiag, rightDiag, board);
        
    }
    generateNthQueen(n, 0, row, col, leftDiag, rightDiag, board);
}
