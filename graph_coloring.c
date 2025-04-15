#include <stdio.h>
#include <stdbool.h>

#define V 4

int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}
};

bool isSafe(int v, int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

bool graphColoringUtil(int m, int color[], int v) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, color, c)) {
            color[v] = c;
            if (graphColoringUtil(m, color, v + 1))
                return true;
            color[v] = 0;
        }
    }
    return false;
}

bool graphColoring(int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(m, color, 0) == false) {
        printf("Solution does not exist\n");
        return false;
    }

    char* colors[] = {"Red", "Green", "Pink", "Blue"};
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> %s\n", i, colors[color[i] - 1]);
    }
    return true;
}

int main() {
    int m = 4;
    graphColoring(m);
    return 0;
}
