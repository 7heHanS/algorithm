#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// BFS 방식 (Kahn's Algorithm)
vector<int> topologicalSortBFS(int n, const vector<vector<int>>& adj) {
    vector<int> in_degree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            ++in_degree[v];
        }
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (topo_order.size() != n) {
        throw runtime_error("Graph has a cycle, topological sort not possible");
    }

    return topo_order;
}

// DFS 방식
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, st);
        }
    }
    st.push(u);
}

vector<int> topologicalSortDFS(int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, st);
        }
    }

    vector<int> topo_order;
    while (!st.empty()) {
        topo_order.push_back(st.top());
        st.pop();
    }

    return topo_order;
}

int main() {
    int n = 6; // Number of vertices
    vector<vector<int>> adj = {
        {2, 3},    // 0 -> 2, 0 -> 3
        {3, 4},    // 1 -> 3, 1 -> 4
        {3},       // 2 -> 3
        {5},       // 3 -> 5
        {5},       // 4 -> 5
        {}         // 5
    };

    try {
        vector<int> topo_order_bfs = topologicalSortBFS(n, adj);
        cout << "Topological Sort (BFS): ";
        for (int v : topo_order_bfs) {
            cout << v << " ";
        }
        cout << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    vector<int> topo_order_dfs = topologicalSortDFS(n, adj);
    cout << "Topological Sort (DFS): ";
    for (int v : topo_order_dfs) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}