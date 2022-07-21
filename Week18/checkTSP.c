#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int routeLength(int n, int *route, int **graph){
    int res = 0;
    for (int i = 0; i < n; ++i){
        int src = route[i] - 1, dest = route[(i + 1) % n] - 1;
        res += graph[src][dest];
    }
    return res;
}
int main(){
    int n, m, *route, *order, **graph;
    scanf("%d", &n);
    route = (int*)calloc(n, sizeof(int));
    order = (int*)calloc(n, sizeof(int));
    graph = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i){
        scanf("%d", &route[i]);
        order[route[i] - 1] = i;
    }
    for (int i = 0; i < n; ++i){
        graph[i] = (int*)calloc(n, sizeof(int));
        for (int j = 0; j < n; ++j) scanf("%d", &graph[i][j]);
    }
    scanf("%d", &m);
    bool feasible = true;
    for (int i = 0; i < m; ++i){
        int dest1, dest2;
        scanf("%d %d", &dest1, &dest2);
        if (order[dest1 - 1] > order[dest2 - 1]) feasible = false;
    }
    printf("%d", feasible ? routeLength(n, route, graph): -1);

}