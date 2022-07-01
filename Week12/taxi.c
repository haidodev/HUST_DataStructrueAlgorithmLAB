#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define MIN(a, b) (a) < (b) ? (a) : (b);
int n;
int *arr, *visited, **tmpGraph, **graph;
int minPath = INT_MAX; 
void permutation(int k, int curPath){
    if (curPath > minPath) return;
    if (k > n) {
        minPath = MIN(minPath, curPath + graph[arr[k - 1]][arr[0]]);
        return;
    }
    for (int i = 1; i <= n; ++i){
        if (visited[i]) continue;
        visited[i] = true;
        arr[k] = i;
        permutation(k + 1, curPath + graph[arr[k - 1]][arr[k]]);
        visited[i] = false;
    }
}
void rebuildGraph(){//int **tmpGraph, int **graph, int n){
    graph = (int**)calloc(n + 1, sizeof(int*));
    graph[0] = (int*)calloc(n + 1, sizeof(int));
    for (int j = 0; j <= n; ++j){
        graph[0][j] = tmpGraph[0][j];
    }
    for (int i = 1; i <= n; ++i){
        graph[i] = (int*)calloc(n + 1, sizeof(int));
        for (int j = 0; j <= n; ++j){
            graph[i][j] = tmpGraph[i][i + n] + tmpGraph[i + n][j];
        }
    }
}
int main(){
    scanf("%d", &n);
    visited = (int*)calloc(n + 1, sizeof(int));
    arr = (int*)calloc(n + 1, sizeof(int));
    arr[0] = 0;
    tmpGraph = (int**)calloc(2 * n + 1, sizeof(int*));
    for (int i = 0; i < 2 * n + 1; ++i){
        tmpGraph[i] = (int*)calloc(2 * n + 1, sizeof(int));
        for (int j = 0; j < 2 * n + 1; ++j){
            scanf("%d", &tmpGraph[i][j]);
        }
    }
    rebuildGraph();
    permutation(1, 0);
    printf("%d", minPath);
}