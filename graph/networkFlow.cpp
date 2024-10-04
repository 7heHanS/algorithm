#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <cstring>

using namespace std;

class NetworkFlow {
    int V; // Number of vertices
    vector<vector<int>> capacity; // Capacity matrix
    vector<vector<int>> adj; // Adjacency list

public:
    NetworkFlow(int V) : V(V), capacity(V, vector<int>(V, 0)), adj(V) {}

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = s;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next]) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t) {
                        return new_flow;
                    }
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        vector<int> parent(V);
        int new_flow;

        while (new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }
};

int main() {
    int V = 6; // Number of vertices
    NetworkFlow nf(V);

    // Add edges with capacities
    nf.addEdge(0, 1, 16);
    nf.addEdge(0, 2, 13);
    nf.addEdge(1, 2, 10);
    nf.addEdge(1, 3, 12);
    nf.addEdge(2, 1, 4);
    nf.addEdge(2, 4, 14);
    nf.addEdge(3, 2, 9);
    nf.addEdge(3, 5, 20);
    nf.addEdge(4, 3, 7);
    nf.addEdge(4, 5, 4);

    int source = 0;
    int sink = 5;

    cout << "The maximum possible flow is " << nf.maxFlow(source, sink) << endl;

    return 0;
}