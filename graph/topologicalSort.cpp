#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// BFS 방식 (Kahn's Algorithm), 사이클 검출 가능
vector<int> topologicalSortBFS(int n, const vector<vector<int>>& adj) {
    vector<int> in_degree(n, 0);

    // 개별 정점 indegree 계산
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            ++in_degree[v];
        }
    }

    // indegree가 0인 정점을 큐에 삽입
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

    // 모든 정점을 방문하지 않았다면 사이클이 존재
    // 사이클이 존재하면 topo_order.size()가 n보다 작다
    if (topo_order.size() != n) {
        throw runtime_error("Graph has a cycle, topological sort not possible");
    }

    return topo_order;
}

// DFS 방식
// DFS 에서 나올 때, stack에 push 후 역순으로 출력하면 위상 정렬이 된다.
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