#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<int>* adj;  // Adjacency list
    vector<bool> visited;
    vector<int> discovery_time;
    vector<int> low;
    vector<int> parent;
    vector<bool> articulation_point;
    int time;

    void DFS(int u) {
        visited[u] = true;
        discovery_time[u] = low[u] = ++time;
        int children = 0;

        // 디버깅: 현재 노드와 시간 정보를 출력
        cout << "DFS visiting node " << u << " at time " << time << endl;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;

                // 디버깅: DFS 재귀 호출 시작
                cout << "DFS recursing to node " << v << " from node " << u << endl;

                DFS(v);

                // Check if the subtree rooted at v has a connection back to one of u's ancestors
                low[u] = min(low[u], low[v]);

                // 디버깅: low 값 업데이트
                cout << "Updated low[" << u << "] = " << low[u] << " after visiting " << v << endl;

                // u is an articulation point in the following cases:
                if (parent[u] == -1 && children > 1) {
                    articulation_point[u] = true;
                    cout << "Node " << u << " is an articulation point (root with multiple children)." << endl;
                }
                if (parent[u] != -1 && low[v] >= discovery_time[u]) {
                    articulation_point[u] = true;
                    cout << "Node " << u << " is an articulation point (low[" << v << "] >= discovery_time[" << u << "])." << endl;
                }
            }
            // Update low[u] for back edge
            else if (v != parent[u]) {
                low[u] = min(low[u], discovery_time[v]);
                cout << "Back edge found from " << u << " to ancestor " << v << ", updated low[" << u << "] to " << low[u] << endl;
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
        visited.assign(V, false);
        discovery_time.assign(V, -1);
        low.assign(V, -1);
        parent.assign(V, -1);
        articulation_point.assign(V, false);
        time = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findArticulationPoints() {
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i);
            }
        }

        for (int i = 0; i < V; i++) {
            if (articulation_point[i]) {
                cout << "Articulation point: " << i << endl;
            }
        }
    }
};

int main() {
    // Create graph
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    g.findArticulationPoints();

    return 0;
}
