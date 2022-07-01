#include<stdio.h>
#include<stdbool.h>
bool checkRow(int row, int board[9][9]){
    int sumCell = 0;
    for (int col = 0; col < 9; ++col){
        sumCell += board[row][col];
    }
    return sumCell == 45;
}
bool checkCol(int col, int board[9][9]){
    int sumCell = 0;
    for (int row = 0; row < 9; ++row){
        sumCell += board[row][col];
    }
    return sumCell == 45;
}
bool checkSmallQuare(int row, int col, int board[9][9]){
    int sumCell = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            sumCell += board[row + i][col + j];
        }
    }
    return sumCell == 45;
}
void fillBoard(int board[9][9]){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            scanf("%d", &board[i][j]);
        }
    }
}
bool checkSudokuBoard(int board[9][9]){
    for (int i = 0; i < 9; ++i){
        if (!checkRow(i, board)){
            return false;
        } 
    }
    for (int i = 0; i < 9; ++i){
        if (!checkCol(i, board)) {
            return false;
        } 
    }
    for (int i = 0; i < 9; i += 3){
        for (int j = 0; j < 9; j += 3){
            if (!checkSmallQuare(i, j, board)) {
                return false;
            } 
        }

    }
    return true;
}
void showBoard(int board[9][9]){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    
}
int main(){
    int testcase, board[9][9];
    scanf("%d", &testcase);
    while (testcase--){
        fillBoard(board);
        printf("%d\n", checkSudokuBoard(board));
    }
    return 0;
}