#include<stdio.h>
#include<stdlib.h>
int countSolution(int cur, int n, int m, int *x, int **range){
    if (cur == n - 1) {
        if (m % x[cur] != 0) return 0;
        int sol = m / x[cur];
        if (sol < range[cur][0] || sol > range[cur][1]) return 0;
        return 1;
    }
    int res = 0;
    for (int i = range[cur][0]; i <= range[cur][1]; ++i){
        res += countSolution(cur + 1, n, m - i * x[cur], x, range);
    }
    return res;
}
int main(){
    int n, m, *x, **range;
    scanf("%d", &n);
    scanf("%d", &m);
    x = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i){
        scanf("%d", &x[i]);
    }
    range = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i){
        range[i] = (int*)calloc(2, sizeof(int));
    }
    for (int i = 0; i < n; ++i){
        scanf("%d", &range[i][0]);
        scanf("%d", &range[i][1]);
    }
    printf("%d", countSolution(0, n, m, x, range));
}