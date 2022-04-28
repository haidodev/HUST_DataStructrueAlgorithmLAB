#include<stdio.h>
int count = 0;
void printBoard(int board[9][9]){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int sudoku(int row, int col, int board[9][9]){
    if (row == 9){
        return 1;
    }
    int nextCol = col + 1, nextRow = row;
    if (nextCol == 9){
        nextCol = 0;
        ++nextRow;
    } 
    int res = 0;
    int mark[10] = {0};
    for (int i = 0; i < 9; ++i) mark[board[row][i]] = 1;
    for (int i = 0; i < 9; ++i) mark[board[i][col]] = 1;
    int upRow = (row / 3) * 3, leftCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            mark[board[upRow + i][leftCol + j]] = 1;
        }
    }
    
    for (int i = 1; i <= 9; ++i){
        if (mark[i] == 0) {
            board[row][col] = i;
            res += sudoku(nextRow, nextCol, board);
            board[row][col] = 0;
        }
    }
    return res;
}
int main(){
    int board[9][9];
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            scanf("%d", &board[i][j]);
        }
    }
    printf("%d", sudoku(0, 0, board));
}