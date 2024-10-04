#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DisjointSetUnion {
    vector<int> parent, rank;
    DisjointSetUnion(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v]) {
                swap(u, v);
            }
            parent[v] = u;
            if (rank[u] == rank[v]) {
                ++rank[u];
            }
        }
    }
};

// Kruskal 알고리즘: 모든 간선을 최소 비용으로 연결하는 최소 비용 신장 트리(Minimum Spanning Tree)를 찾는 알고리즘
// 간선 중심 접근 방식, 간선 정렬 필요, 희소 그래프(간선의 수가 적은 경우)에 적합
// 시간 복잡도: O(ElogE)
int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DisjointSetUnion dsu(n);
    int mst_weight = 0;
    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst_weight += edge.weight;
            cout << "Edge: " << edge.u << " - " << edge.v << " Weight: " << edge.weight << endl;
        }
    }
    return mst_weight;
}

// Prim 알고리즘: 모든 정점을 최소 비용으로 연결하는 최소 비용 신장 트리(Minimum Spanning Tree)를 찾는 알고리즘
// 정점 중심 접근 방식, 우선순위 큐 사용, 밀집 그래프(간선의 수가 많은 경우)에 적합
// 시간 복잡도: O(ElogV)
int prim(int n, vector<Edge>& edges) {
    vector<vector<pair<int, int>>> adj(n);
    for (const auto& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.weight});
        adj[edge.v].push_back({edge.u, edge.weight});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> inMST(n, false);
    int mst_weight = 0;

    pq.push({0, 0}); // {weight, vertex}

    while (!pq.empty()) {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mst_weight += weight;
        cout << "Include vertex: " << u << " with weight: " << weight << endl;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    return mst_weight;
}

int main() {
    int n = 4; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    cout << "Kruskal MST weight: " << kruskal(n, edges) << endl;
    cout << "Prim MST weight: " << prim(n, edges) << endl;

    return 0;
}