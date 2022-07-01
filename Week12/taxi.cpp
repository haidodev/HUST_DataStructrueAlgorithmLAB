#include <bits/stdc++.h>
using namespace std;
struct Node{
    struct Node *next;
    int pathLen, mask, prevNode;
};
typedef struct Node LinkedList;
int **tmpGraph, **graph, *visited, *arr, n;
int minPath = INT_MAX;
int evaluatePath(int **graph, int *arr, int n)
{
    int prevPos = 0, curPath = 0;
    for (int i = 0; i < n; ++i)
    {
        curPath += graph[prevPos][arr[i]];
        prevPos = arr[i];
    }
    curPath += graph[prevPos][0];
    return curPath;
}
void permutation(int k)
{
    if (k == n)
    {

        minPath = min(minPath, evaluatePath(graph, arr, n));
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (visited[i])
            continue;
        visited[i] = true;
        arr[k] = i;
        permutation(k + 1);
        visited[i] = false;
    }
}
void rebuildGraph(){
    graph = (int **)calloc(n + 1, sizeof(int *));
    graph[0] = (int *)calloc(n + 1, sizeof(int));
    for (int j = 0; j <= n; ++j)
    {
        graph[0][j] = tmpGraph[0][j];
    }
    for (int i = 1; i <= n; ++i)
    {
        graph[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j <= n; ++j)
        {
            graph[i][j] = tmpGraph[i][i + n] + tmpGraph[i + n][j];
        }
    }
}
void printArray(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}
void print2DArray(int **arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printArray(arr[i], n);
    }
}
void appendToBack(LinkedList **head, LinkedList **tail, int pathLen, int mask, int prevNode){
    LinkedList *newNode = (LinkedList*)malloc(sizeof(LinkedList));
    newNode -> mask = mask;
    newNode -> prevNode = prevNode;
    *tail = newNode;
    if (!(*head)) *head = newNode;
}
void popAtFront(LinkedList **head, LinkedList **tail){
    LinkedList *tmpNode = *head;
    if (*head == *tail) {
        *head = NULL;
        *tail = NULL;
    } else *head = tmpNode -> next;
    free(tmpNode);
}
void myMemset(int *arr, int value, int arrsz){
    for (int i = 0; i < arrsz; ++i) arr[i] = value;
}
void dijkstra(){
    int *distance;
    distance = (int*)calloc(pow(2, n) + 1, sizeof(int));
    myMemset(distance, INT_MAX, pow(2, n) + 1);
    LinkedList *head, *tail;
    appendToBack(&head, &tail, 0, 0, 0);

    while (head){
        int mask = head -> mask, prevNode = head -> prevNode;
        int tmp = mask;
        for (int i = 0; i < n; ++i){
            if (tmp % 2 == 0) {
                int curMask = pow(2, n);
                curMask |= mask;
                if (distance[curMask] > distance[mask] + graph[prevNode + 1][i + 1]){
                    distance[curMask] = distance[mask] + graph[prevNode + 1][i + 1];
                    appendToBack(&head, &tail, distance[curMask], curMask, i);
                }
            }
            tmp /= 2;
        }
    }
}
void readGraph(){
    ifstream fi("TAXI.INP");
    fi >> n;
    tmpGraph = (int **)calloc(2 * n + 1, sizeof(int *));
    for (int i = 0; i < 2 * n + 1; ++i)
    {
        tmpGraph[i] = (int *)calloc(2 * n + 1, sizeof(int));
        for (int j = 0; j < 2 * n + 1; ++j)
        {
            fi >> tmpGraph[i][j];
        }
        
    }
    fi.close();
}
int main()
{
    readGraph();
    rebuildGraph();
    visited = (int*)calloc(n + 1, sizeof(int));
    arr = (int*)calloc(n, sizeof(int));
    //print2DArray(tmpGraph, 2 * n + 1);
    //print2DArray(graph, n + 1);
    permutation(0);
    printf("%d", minPath);
}