#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void showChessBoard(int *col, int n)
{

    for (int i = 0; i < n; ++i)
    {
        printf("\"");
        for (int j = 0; j < n; ++j)
        {
            if (col[j] == i + 1)
                printf("Q");
            else
                printf(".");
        }
        printf("\",\n");
    }
    for (int i = 0; i < n; ++i)
    {
        printf("-");
    }
    printf("\n");
}
bool maskCell(int n, int i, int j, int *col, int *leftDiag, int *rightDiag)
{
    int rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    if (col[j] != 0 || leftDiag[leftDiagIndex] != 0 || rightDiag[rightDiagIndex] != 0)
        return false;
    col[j] = i + 1;
    leftDiag[leftDiagIndex] = 1;
    rightDiag[rightDiagIndex] = 1;
    return true;
}
void unMaskCell(int n, int i, int j, int *col, int *leftDiag, int *rightDiag)
{
    int rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
    col[j] = 0;
    leftDiag[leftDiagIndex] = 0;
    rightDiag[rightDiagIndex] = 0;
}
int generateNthQueen(int n, int i, int *row, int *col, int *leftDiag, int *rightDiag)
{

    if (i == n)
    {
        return 1;
    }
    if (row[i] == 1)
        return generateNthQueen(n, i + 1, row, col, leftDiag, rightDiag);
    int res = 0;
    for (int j = 0; j < n; ++j)
    {
        int rightDiagIndex = j + (n - i - 1), leftDiagIndex = j + i;
        if (col[j] == 0 && leftDiag[leftDiagIndex] == 0 && rightDiag[rightDiagIndex] == 0)
        {

            maskCell(n, i, j, col, leftDiag, rightDiag);
            res += generateNthQueen(n, i + 1, row, col, leftDiag, rightDiag);
            unMaskCell(n, i, j, col, leftDiag, rightDiag);
        }
    }
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);
    char **board = (char **)calloc(n, sizeof(char *));
    for (int i = 0; i < n; ++i)
    {
        board[i] = (char *)calloc(n, sizeof(char));
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            board[i][j] = '.';
        }
    }
    int *col = (int *)calloc(n, sizeof(int)), *row = (int *)calloc(n, sizeof(int)), *leftDiag = (int *)calloc(2 * n - 1, sizeof(int)), *rightDiag = (int *)calloc(2 * n - 1, sizeof(int));
    int prevQueen = 0;
    scanf("%d", &prevQueen);
    while (prevQueen--)
    {
        int r, c;
        scanf("%d", &r);
        scanf("%d", &c);
        --r;
        --c;
        row[r] = 1;
        if (!maskCell(n, r, c, col, leftDiag, rightDiag))
        {
            printf("0\n");
            return 0;
        }
    }
    printf("%d\n", generateNthQueen(n, 0, row, col, leftDiag, rightDiag));
}
