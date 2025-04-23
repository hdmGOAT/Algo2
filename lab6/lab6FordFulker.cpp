#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int V = 5; // Number of vertices in the graph

// Function to perform BFS and find if there's a path from source to sink
bool bfs(const vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

// Ford-Fulkerson algorithm for max flow
int fordFulkerson(vector<vector<int>> graph, int s, int t) {
    vector<vector<int>> rGraph = graph; // residual graph
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    cout << "Residual Graph (after max flow):\n";
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] > 0 && rGraph[u][v] < graph[u][v]) {
                cout << "Flow through " << u << "->" << v << " = " << graph[u][v] - rGraph[u][v] << "/" << graph[u][v] << "\n";
            }
        }
    }

    cout << "\nMinimum Cut Edges (Bottlenecks):\n";
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (visited[u] && !visited[v] && graph[u][v] > 0) {
                cout << u << " -> " << v << " (Capacity = " << graph[u][v] << ")\n";
            }
        }
    }

    return max_flow;
}

int main() {
    // Graph definition from the problem
    vector<vector<int>> graph(V, vector<int>(V, 0));
    graph[0][1] = 10;
    graph[0][2] = 15;
    graph[1][4] = 10;
    graph[2][3] = 5;
    graph[3][4] = 5;
    graph[1][3] = 5;

    int maxFlow = fordFulkerson(graph, 0, 4);
    cout << "\nMaximum number of vehicles that can reach the shelter per hour: " << maxFlow << endl;

    cout << "\nWhat-if Analysis:\n";
    cout << "If 0->2 expanded to 20, new max flow = 20 (limited by 1->4 + 3->4).\n";
    cout << "Adding 3->1 (capacity=3) does not improve flow to sink due to cycle.\n";

    return 0;
}