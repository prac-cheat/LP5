#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

void printAdjList(const vector<vector<int>>& adj) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for (int j : adj[i]) cout << j << " ";
        cout << endl;
    }
}

void bfs(vector<vector<int>>& adj, int start) {
    queue<int> q;
    vector<bool> visited(adj.size(), false);
    
    q.push(start);
    visited[start] = true;

    cout << "\nParallel BFS Traversal: ";
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        #pragma omp parallel for
        for (int j = 0; j < adj[node].size(); j++) {
            int neighbor = adj[node][j];

            #pragma omp critical
            {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: "; cin >> V;
    cout << "Enter number of edges: "; cin >> E;

    vector<vector<int>> adj(V);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    int start;
    cout << "Enter BFS starting node: "; cin >> start;

    printAdjList(adj);
    bfs(adj, start);

    return 0;
}