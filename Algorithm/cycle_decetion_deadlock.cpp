#include <bits/stdc++.h>
using namespace std;

class DeadlockDetector {
    int V; // total vertices (processes + resources)
    vector<vector<int>> adj;
    vector<bool> visited, recStack;

public:
    void init() {
        cout << "Enter total number of vertices (processes + resources): ";
        cin >> V;
        adj.resize(V);
        visited.resize(V, false);
        recStack.resize(V, false);

        int edges;
        cout << "Enter total number of edges: ";
        cin >> edges;
        cout << "Enter edges (from -> to):\n";
        for(int i = 0; i < edges; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
    }

    bool dfs(int v) {
        visited[v] = true;
        recStack[v] = true;

        for(int neighbor : adj[v]) {
            if(!visited[neighbor] && dfs(neighbor))
                return true;
            else if(recStack[neighbor])
                return true;
        }

        recStack[v] = false;
        return false;
    }

    void detectDeadlock() {
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                if(dfs(i)) {
                    cout << "Deadlock detected via cycle in the graph.\n";
                    return;
                }
            }
        }
        cout << "No deadlock detected. System is safe.\n";
    }
};

int main() {
    DeadlockDetector dd;
    dd.init();
    dd.detectDeadlock();
    return 0;
}
