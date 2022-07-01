#include<stdio.h>
#include<stdlib.h>
int blackCol(int **matrix, int n, int m){
    int res = 0;
    for (int j = 0; j < m; ++j){
        int cur = 1;
        for (int i = 0; i < n; ++i){
            if (matrix[i][j] == 0) cur = 0;
        }
        res += cur;
    }
    return res;
}
int main(){
    int m, n;
    scanf("%d %d", &n, &m);
    int **matrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i){
        matrix[i] = (int*)calloc(m, sizeof(int));
        for (int j = 0; j < m; ++j){
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("%d", blackCol(matrix, n, m));
    return 0;
}