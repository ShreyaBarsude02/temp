#include <iostream>
#include <vector>
using namespace std;

int isSafe(int v, int c, vector<vector<int>>& adj, vector<int>& colors) {
    for (int i = 0; i < adj[v].size(); i++) {
        int neighbor = adj[v][i];
        if (colors[neighbor] == c) {
            return 0;
        }
    }
    return 1;
}

int graphColoring(int i, int n, int m, vector<vector<int>>& adj, vector<int>& colors) {
    if (i == n) {
        return 1;
    }
    for (int c = 1; c <= m; c++) {
        if (isSafe(i, c, adj, colors)) {
            colors[i] = c;
            if (graphColoring(i + 1, n, m, adj, colors)) {
                return 1;
            }
            colors[i] = 0;
        }
    }
    return 0;
}

int main() {
    int n = 4;
    int m = 3;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2, 3};
    adj[1] = {0, 2};
    adj[2] = {0, 1, 3};
    adj[3] = {0, 2};
    vector<int> colors(n, 0);

    if (graphColoring(0, n, m, adj, colors)) {
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i << " ---> Color " << colors[i] << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }
    return 0;
}
