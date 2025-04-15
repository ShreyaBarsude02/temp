#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF 9999

int graph[MAX][MAX][MAX]; // node -> (group of children in one AND/OR set) -> child node
int cost[MAX][MAX];       // node -> cost of each AND/OR group
int status[MAX];          // 0 = solved, 1 = pending
int solved[MAX];          // final solved path
int h[MAX];               // heuristic values
int n;                    // total number of nodes

int findMinCost(int node, int* next) {
    int min = INF, bestGroup = -1;

    for (int i = 0; i < MAX && cost[node][i] != -1; i++) {
        int total = 0;
        for (int j = 0; graph[node][i][j] != -1; j++) {
            int child = graph[node][i][j];
            total += h[child];
        }
        total += cost[node][i];

        if (total < min) {
            min = total;
            bestGroup = i;
        }
    }

    *next = bestGroup;
    return min;
}

void AOStar(int node) {
    if (status[node] == 0)
        return;

    int nextGroup = -1;
    h[node] = findMinCost(node, &nextGroup);

    int solvable = 1;
    for (int j = 0; graph[node][nextGroup][j] != -1; j++) {
        int child = graph[node][nextGroup][j];
        if (status[child] != 0) {
            solvable = 0;
            AOStar(child);
        }
    }

    if (solvable) {
        status[node] = 0;
        solved[node] = nextGroup;
    }
}

void printSolution(int node) {
    if (status[node] == 0) {
        printf("%c", node + 'A');
        int group = solved[node];
        if (graph[node][group][1] != -1)
            printf(" -> (");

        for (int i = 0; graph[node][group][i] != -1; i++) {
            printf("%c", graph[node][group][i] + 'A');
            if (graph[node][group][i + 1] != -1)
                printf(" + ");
        }

        if (graph[node][group][1] != -1)
            printf(")");

        printf("\n");

        for (int i = 0; graph[node][group][i] != -1; i++)
            printSolution(graph[node][group][i]);
    }
}

int main() {
    n = 6;

    for (int i = 0; i < MAX; i++) {
        status[i] = 1;
        solved[i] = -1;
        h[i] = 999;
        for (int j = 0; j < MAX; j++) {
            cost[i][j] = -1;
            for (int k = 0; k < MAX; k++)
                graph[i][j][k] = -1;
        }
    }

    // Example AO* graph:
    // A -> (B + C)[3] OR D[2]
    // B -> E[2]
    // C -> F[4]
    cost[0][0] = 3; graph[0][0][0] = 1; graph[0][0][1] = 2;
    cost[0][1] = 2; graph[0][1][0] = 3;

    cost[1][0] = 2; graph[1][0][0] = 4;
    cost[2][0] = 4; graph[2][0][0] = 5;

    h[4] = 0; status[4] = 0;
    h[5] = 0; status[5] = 0;
    h[3] = 0; status[3] = 0;

    AOStar(0);

    printf("Solution Path:\n");
    printSolution(0);

    return 0;
}
