#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

Stack* createStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (s->top < MAX - 1) s->items[++s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) return -1;
    return s->items[s->top--];
}

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph* graph, int startVertex) {
    Stack* stack = createStack();
    push(stack, startVertex);
    while (!isEmpty(stack)) {
        int current = pop(stack);
        if (!graph->visited[current]) {
            printf("%d ", current);
            graph->visited[current] = 1;
        }
        Node* temp = graph->adjLists[current];
        while (temp) {
            if (!graph->visited[temp->vertex]) {
                push(stack, temp->vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices = 5;
    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    DFS(graph, 0);
    return 0;
}
