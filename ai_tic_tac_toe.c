#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX_V];
int colors[MAX_V];

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

int isSafe(int vertex, int c) {
    Node* temp = adjList[vertex];
    while (temp != NULL) {
        if (colors[temp->vertex] == c)
            return 0;
        temp = temp->next;
    }
    return 1;
}

int graphColoring(int i, int V, int M) {
    if (i == V)
        return 1;

    for (int c = 1; c <= M; c++) {
        if (isSafe(i, c)) {
            colors[i] = c;
            if (graphColoring(i + 1, V, M))
                return 1;
            colors[i] = 0;
        }
    }
    return 0;
}

void printColors(int V) {
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, colors[i]);
}

int main() {
    int V = 4;
    int M = 3;

    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
        colors[i] = 0;
    }

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 3);

    if (graphColoring(0, V, M))
        printColors(V);
    else
        printf("Solution does not exist.\n");

    return 0;
}
