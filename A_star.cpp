#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <climits>
using namespace std;

typedef pair<int, int> pii;
typedef pair<float, int> pfi;

float heuristic(int a, int b) {
    return abs(a - b); 
}

void aStar(int start, int goal, unordered_map<int, vector<pii>> &adjList) {
    unordered_map<int, float> gScore;
    unordered_map<int, float> fScore;
    unordered_map<int, int> cameFrom;

    for (auto &node : adjList) {
        gScore[node.first] = INT_MAX;
        fScore[node.first] = INT_MAX;
    }

    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);

    priority_queue<pfi, vector<pfi>, greater<pfi>> openSet;
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        int current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            cout << "Path: ";
            while (cameFrom.find(current) != cameFrom.end()) {
                cout << current << " <- ";
                current = cameFrom[current];
            }
            cout << start << endl;
            return;
        }

        for (auto &neighbor : adjList[current]) {
            int neighborNode = neighbor.first;
            int weight = neighbor.second;

            float tentative_gScore = gScore[current] + weight;
            if (tentative_gScore < gScore[neighborNode]) {
                cameFrom[neighborNode] = current;
                gScore[neighborNode] = tentative_gScore;
                fScore[neighborNode] = tentative_gScore + heuristic(neighborNode, goal);
                openSet.push({fScore[neighborNode], neighborNode});
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    unordered_map<int, vector<pii>> adjList;
    adjList[0] = {{1, 1}, {3, 4}};
    adjList[1] = {{2, 2}};
    adjList[2] = {{3, 1}};
    adjList[3] = {};

    int start = 0, goal = 3;
    aStar(start, goal, adjList);

    return 0;
}
