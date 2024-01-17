#include <stdio.h>
#include <stdlib.h>

/*
Graph traversal ; depth first search, breath first search with adjacency list

Minimum cost spanning tree ; kruskal, prim, sollin

Shortest path searching ; dijkstra, bellman-ford (to be implemented)
*/

typedef struct list* listPointer;
typedef struct list {
    int data;
    listPointer link;
}list;

listPointer graphPointer[9];
listPointer curr;

int dupArr[9] = { 0, };  // duplication checking arr.

void add(listPointer prev, int num) {
    listPointer temp = (listPointer)malloc(sizeof(list));
    temp->data = num;
    temp->link = NULL;
    prev->link = temp;
    curr = temp;
}

void setAdjacencyList() {
    // make adjacency list first
    for (int i = 0; i < 9; i++) {
        graphPointer[i] = (listPointer)malloc(sizeof(list));
        graphPointer[i]->data = i;
        graphPointer[i]->link = NULL;
    }

    add(graphPointer[0], 1);
    add(curr, 3);
    add(curr, 8);

    add(graphPointer[1], 0);
    add(curr, 7);

    add(graphPointer[2], 3);
    add(curr, 5);
    add(curr, 7);

    add(graphPointer[3], 0);
    add(curr, 2);
    add(curr, 4);

    add(graphPointer[4], 3);
    add(curr, 5);
    add(curr, 8);

    add(graphPointer[5], 2);
    add(curr, 4);
    add(curr, 6);

    add(graphPointer[6], 5);

    add(graphPointer[7], 1);
    add(curr, 2);

    add(graphPointer[8], 0);
    add(curr, 4);
}

void showAdjacencyList() {

    printf("ADJACENCY LIST\n--------------\n");
    for (int i = 0; i < 9; i++) {
        for (listPointer temp = graphPointer[i]; temp; temp = temp->link) {
            printf("%d ", temp->data);
            if (!temp->link) break;
            printf("-> ");
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(int startingNum) {    //depth first search.
    printf("%d ", startingNum);
    dupArr[startingNum] = 1;    // dupArr; duplication check
    for (listPointer temp = graphPointer[startingNum]->link; temp; temp = temp->link) {
        if (!dupArr[temp->data]) dfs(temp->data);
        if (!temp->link) break;
    }
}

int main() {

    setAdjacencyList();
    showAdjacencyList();
    printf("dfs : ( ");
    dfs(0);
    printf(")\n");

    return 0;
}