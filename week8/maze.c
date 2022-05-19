#include<stdio.h>
#include<stdlib.h>
struct Node {
    int row, col, step;
    struct Node *next;
};
typedef struct Node LinkedList;
void insertToBack(LinkedList **tail, int cellRow, int cellCol, int cellStep){
    LinkedList *currentNode = (LinkedList*)malloc(sizeof(LinkedList));
    currentNode -> row = cellRow;
    currentNode -> col = cellCol;
    currentNode -> step = cellStep;
    if (*tail) (*tail) -> next = currentNode;
    *tail = currentNode;
}
void getTopElement(LinkedList *head, int *cellRow, int *cellCol, int *cellStep){
    if (!(head)) return;
    *cellRow = (head) -> row;
    *cellCol = (head) -> col;
    *cellStep = (head) -> step;
}
void deleteAtFront(LinkedList **head){
    LinkedList *currentNode = *head;
    (*head) = (*head) -> next;
    free(currentNode);
}
int breathFirstSearch(int **grid, int numRow, int numCol, int startRow, int startCol){
    LinkedList *head = NULL, *tail = NULL;
    int dir[5] = {1, 0, -1, 0, 1};
    int **visited;
    visited = (int**)calloc(numRow, sizeof(int*));
    for (int i = 0; i < numRow; ++i) visited[i] = (int*)calloc(numCol, sizeof(int));
    
    insertToBack(&tail, startRow, startCol, 0);
    visited[startRow][startCol] = 1;
    head = tail;
    while (head){
        int curRow, curCol, curStep;
        getTopElement(head, &curRow, &curCol, &curStep);
        for (int i = 0; i < 4; ++i){
            int nextRow = curRow + dir[i], nextCol = curCol + dir[i + 1];
            if (nextRow < 0 || nextRow >= numRow || nextCol < 0 || nextCol >= numCol) return curStep + 1;
            if (visited[nextRow][nextCol] || grid[nextRow][nextCol]) continue;
            visited[nextRow][nextCol] = 1;
            insertToBack(&tail, nextRow, nextCol, curStep + 1);
        }
        deleteAtFront(&head);
    }
    return -1;
}
int main(){
    int numRow, numCol, startRow, startCol;
    scanf("%d %d %d %d", &numRow, &numCol, &startRow, &startCol);
    int **grid;
    grid = (int**)calloc(numRow, sizeof(int*));
    for (int i = 0; i < numRow; ++i) grid[i] = (int*)calloc(numCol, sizeof(int));
    for (int i = 0; i < numRow; ++i){
        for (int j = 0; j < numCol; ++j){
            scanf("%d", &grid[i][j]);
        }
    }
    printf("%d", breathFirstSearch(grid, numRow, numCol, startRow - 1, startCol - 1));
}
