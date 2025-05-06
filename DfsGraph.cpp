#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void dfs(vector<vector<int>>& adj, vector<bool>& visited, int node) {
    #pragma omp critical
    {
        if (visited[node]) return; // Avoid duplicate visits
        visited[node] = true;
        cout << node << " ";
    }

    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int neighbor = adj[node][i];
        dfs(adj, visited, neighbor); // Recursive DFS call
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> adj(V);
    vector<bool> visited(V, false);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter edges (u v format):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Remove this for a directed graph
    }

    int start;
    cout << "Enter starting node for DFS: ";
    cin >> start;

    cout << "\nParallel DFS Traversal: ";
    dfs(adj, visited, start);
    cout << endl;

    return 0;
}