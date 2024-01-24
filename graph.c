#include <stdio.h>
#include <stdlib.h>

#define WEIGHTNUM 11
#define NODENUM 9
#define TRUE 1
#define FALSE 0

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

int queue[9] = { 0, };
int front = 0;   // front, rear for queue push & pop operation
int rear = 0;

int** arr = NULL;
int count = 0;

int unionFindArr[9];

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

void push(int num) {    // both push and pop are implemented without exception handler
    queue[rear++] = num;
}

int pop() {
    return queue[front++];
}

void bfs(int startingNum) { //breadth first search
    //using queue
    listPointer temp = NULL;
    int index = startingNum;
    for (int i = 0; i < 9; i++) dupArr[i] = 0; // check duplication
    printf("%d ", startingNum);
    dupArr[startingNum] = 1;

    while (1) {
        if (front == rear && front != 0) break;
        for (temp = graphPointer[index]->link; temp; temp = temp->link) {
            if (!dupArr[temp->data]) {
                push(temp->data);
                printf("%d ", temp->data);
                dupArr[temp->data] = 1;
            }
            if (!temp->link) break;
        }
        index = pop();
    }
}

void addArray(int start, int end, int weight) {
    arr[count][0] = start;
    arr[count][1] = end;
    arr[count++][2] = weight;
}

void setArray() {
    arr = (int**)malloc(sizeof(int*) * WEIGHTNUM);
    for (int i = 0; i < WEIGHTNUM; i++) {
        *(arr + i) = (int*)malloc(sizeof(int) * 3);
    }
    addArray(0, 1, 3);
    addArray(0, 3, 2);
    addArray(0, 8, 5);
    addArray(1, 7, 4);
    addArray(2, 3, 6);
    addArray(2, 7, 7);
    addArray(2, 5, 1);
    addArray(3, 4, 11);
    addArray(4, 8, 10);
    addArray(4, 5, 8);
    addArray(5, 6, 9);
}

void freeArray() {
    for (int i = 0; i < WEIGHTNUM; i++) {
        free(*(arr + i));
    }
    free(arr);
}

void bubble() {
    int temp = 0;
    for (int i = 0; i < WEIGHTNUM; i++) {
        for (int j = 0; j < WEIGHTNUM - i - 1; j++) {
            if (arr[j][2] > arr[j + 1][2]) {
                for (int k = 0; k < 3; k++) {
                    temp = arr[j][k];
                    arr[j][k] = arr[j + 1][k];
                    arr[j + 1][k] = temp;
                }
            }
        }
    }
}

int find(int var) {
    if (unionFindArr[var] == var) return var;
    else return find(unionFindArr[var]);
}

int unionSets(int a, int b) {
    if (find(a) == find(b)) return TRUE;
    else return FALSE;
}

// 주의 !! 작은걸로 하는게 아니라 먼저 들어온 순서대로 해야함 !!
void makeUnionSets(int a, int b) {
    if (find(a) > find(b)) unionFindArr[a] = b;
    else unionFindArr[b] = a;
    // 숫자는 클 수 있어도, 해당 숫자의 대표가 자기보다 작으면 큰 숫자를 따라가야함.
}

void kruskal() { // find min weight which does not make circle and connect
    setArray(); // start, end, weight in double dimension arr
    // use bubble sort to make arr ascending order.
    bubble();
    // union-find ; just like tree...
    // we put two number in union function, which makes them 'union'
    int weight = 0;

    for (int i = 0; i < NODENUM; i++) unionFindArr[i] = i;

    printf("kruskal : [ ");

    for (int i = 0; i < WEIGHTNUM; i++) {
        if (!unionSets(arr[i][0], arr[i][1])) {
            printf("(%d,%d) ", arr[i][0], arr[i][1]);
            makeUnionSets(arr[i][0], arr[i][1]);
            weight += arr[i][2];
        }
    }

    printf("] weight : %d\n", weight);

    freeArray();
}

void prim(int start) {
    // method; just pick up a node, link that node with least weight on and on and on.
    // check if there is a cycle.
    // using group T, put visited node in T array.
    count = 0;
    setArray();
    int visited[9] = { 0, };    //not visited > 0 , visited > 1
    visited[start] = 1;
    int memory;
    int min;
    int node;
    int flag;
    int initialize = 0;
    int weight = 0;

    printf("prim : [ %d ", start);

    while (1) {
        //judging process 
    
        flag = 0;    // 1. which node to start?   2. linked?   3. visited?    4. initialized?     5. minimum?
        min = 0xffff;
        for (int k = 0; k < 9; k++) {
            if (visited[k]) {
                node = k;
                for (int i = 0; i < WEIGHTNUM; i++) { // find node linked with node, and compare weight using min value
                    if (arr[i][0] == node) {
                        if (!visited[arr[i][1]]) {
                            flag = 1;
                            if (!initialize) {
                                min = arr[i][2];
                                initialize = 1;
                                memory = arr[i][1];
                            }
                            else {
                                if (min > arr[i][2]) {
                                    memory = arr[i][1];
                                    min = arr[i][2];
                                }
                            }
                        }
                    }
                    else if (arr[i][1] == node) {
                        if (!visited[arr[i][0]]) {
                            flag = 1;
                            if (!initialize) {
                                min = arr[i][2];
                                initialize = 1;
                                memory = arr[i][0];
                            }
                            else {
                                if (min > arr[i][2]) {
                                    memory = arr[i][0];
                                    min = arr[i][2];
                                }
                            }
                        }
                    }
                }
            }
        }
        // in memory, there is a node which is linked with given node with minimum weight 
        if (!flag) break;
        visited[memory] = 1;
        node = memory;
        printf("%d ", node);
        weight +=min;
    }
    // 3333이 나온다 > 1. flag 씀. 2. min값이 갱신이 안됨.
    printf("] weight : %d\n", weight);
}


int main() {

    setAdjacencyList();
    showAdjacencyList();
    printf("dfs : ( ");
    dfs(0);
    printf(")\n");

    printf("bfs : ( ");
    bfs(0);
    printf(")\n");

    kruskal();
    prim(0);

    return 0;
}