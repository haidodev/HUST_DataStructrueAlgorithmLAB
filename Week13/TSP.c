#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define MIN(a, b) (a) < (b) ? (a) : (b);
int n;
int *arr, *visited, **graph;
int minPath = INT_MAX; 
void permutation(int k, int curPath){
    if (curPath > minPath) return;
    if (k == n) {
        minPath = MIN(minPath, curPath + graph[arr[k - 1]][arr[0]]);
        return;
    }
    for (int i = 1; i < n; ++i){
        if (visited[i]) continue;
        visited[i] = true;
        arr[k] = i;
        permutation(k + 1, curPath + graph[arr[k - 1]][arr[k]]);
        visited[i] = false;
    }
}

int main(){
    scanf("%d", &n);
    visited = (int*)calloc(n, sizeof(int));
    arr = (int*)calloc(n, sizeof(int));
    arr[0] = 0;
    graph = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i){
        graph[i] = (int*)calloc(n, sizeof(int));
        for (int j = 0; j < n; ++j){
            scanf("%d", &graph[i][j]);
        }
    }
    permutation(1, 0);
    printf("%d", minPath);
}