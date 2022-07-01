#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define MIN(a, b) (a) < (b) ? (a) : (b);
int n, K, Q;
int *weight, *visited, *curWeight, *pos, *cnt, **graph;
int curPath = 0, minPath = INT_MAX; 
void backTracking(int passengerLeft){
    if (passengerLeft == 0){
        for (int i = 0; i < K; ++i) if (cnt[i] == 0) return;
        for (int i = 0; i < K; ++i) curPath += graph[pos[i]][0];
        minPath = MIN(minPath, curPath);
        for (int i = 0; i < K; ++i) curPath -= graph[pos[i]][0];
        return;
    }
    for (int curPassenger = 1; curPassenger <= n; ++curPassenger){
        if (visited[curPassenger]) continue;
        for (int i = 0; i < K; ++i){
            int prevPos = pos[i], prevWeight = curWeight[i];
            if (curWeight[i] + weight[curPassenger] < Q){
                ++cnt[i];
                curWeight[i] += weight[curPassenger];
                curPath += graph[prevPos][curPassenger];
                pos[i] = curPassenger;
                visited[curPassenger] = 1;
                backTracking(passengerLeft - 1);
                --cnt[i];
                curWeight[i] -= weight[curPassenger];
                curPath -= graph[prevPos][curPassenger];
                pos[i] = prevPos;
                visited[curPassenger] = 0;
            } else {
                if (weight[i] < Q){
                    ++cnt[i];
                    curWeight[i] = weight[curPassenger];
                    curPath += (graph[pos[i]][0] + graph[0][curPassenger]);
                    pos[i] = curPassenger;
                    visited[curPassenger] = 1;
                    backTracking(passengerLeft - 1);
                    --cnt[i];
                    curWeight[i] = prevWeight;
                    curPath -= (graph[prevPos][0] + graph[0][curPassenger]);
                    pos[i] = prevPos;
                    visited[curPassenger] = 0;
                }
                
            }
        }
    }
    
}
int main(){
    scanf("%d %d %d", &n, &K, &Q);
    weight = (int*)calloc(n + 1, sizeof(int));
    visited = (int*)calloc(n + 1, sizeof(int));
    curWeight = (int*)calloc(K, sizeof(int));
    cnt = (int*)calloc(K, sizeof(int));
    pos = (int*)calloc(K, sizeof(int));
    for (int i = 1; i < n + 1; ++i){
        scanf("%d", &weight[i]);
    }
    graph = (int**)calloc(n + 1, sizeof(int*));
    for (int i = 0; i < n + 1; ++i){
        graph[i] = (int*)calloc(n + 1, sizeof(int));
        for (int j = 0; j < n + 1; ++j){
            scanf("%d", &graph[i][j]);
        }
    }
    backTracking(n);
    printf("%d", minPath);
}