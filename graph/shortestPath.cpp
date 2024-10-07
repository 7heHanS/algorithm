#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <deque>

using namespace std;

const int INF = numeric_limits<int>::max();

// Dijkstra's algorithm
// PRIM과 유사하게 PQ를 이용하여, 최소 거리 정점을 선택하고, 해당 정점을 기준으로 인접 정점들을 업데이트
void dijkstra(int src, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// Bellman-Ford algorithm
// 음수 가중치가 있는 경우에도 사용 가능하며, n번 반복 시 거리 갱신 시 음수 가중치 사이클 존재 (false 반환)
bool bellmanFord(int src, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[src] = 0;

    // Relax edges up to n-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < n; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                return false; // Negative weight cycle found
            }
        }
    }

    return true; // No negative weight cycle found
}

// SPFA algorithm
// Bellman-Ford의 최적화 버전으로, 큐에 정점을 추가할 때, 해당 정점의 거리가 갱신되면 큐에 추가
bool spfa(int src, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    vector<bool> inQueue(n, false);
    deque<int> q;

    dist[src] = 0;
    q.push_back(src);
    inQueue[src] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inQueue[u] = false;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                if (!inQueue[v]) {
                    if (!q.empty() && dist[v] < dist[q.front()]) {
                        q.push_front(v); // Push to front if it can potentially shorten the path
                    } else {
                        q.push_back(v);
                    }
                    inQueue[v] = true;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < n; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                return false; // Negative weight cycle found
            }
        }
    }

    return true; // No negative weight cycle found
}

// Floyd-Warshall algorithm
// 벨반포드 n번 반복과 동일, 음수 가중치 사용 가능, 모든 정점 쌍의 최단 거리를 구함
void floydWarshall(const vector<vector<pair<int, int>>>& graph, vector<vector<int>>& dist) {
    int n = graph.size();
    dist.assign(n, vector<int>(n, INF));

    // Initialize distances with given edges
    for (int u = 0; u < n; ++u) {
        dist[u][u] = 0;
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            dist[u][v] = weight;
        }
    }

    // Dynamic programming to find all pairs shortest paths
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 5; // Number of vertices
    vector<vector<pair<int, int>>> graph(n);

    // Example graph edges (u, v, weight)
    graph[0].push_back({1, 10});
    graph[0].push_back({4, 5});
    graph[1].push_back({2, 1});
    graph[1].push_back({4, 2});
    graph[2].push_back({3, 4});
    graph[3].push_back({0, 7});
    graph[3].push_back({2, 6});
    graph[4].push_back({1, 3});
    graph[4].push_back({2, 9});
    graph[4].push_back({3, 2});

    vector<int> dist;

    // Dijkstra's algorithm
    dijkstra(0, graph, dist);
    cout << "Dijkstra's algorithm:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Distance from 0 to " << i << " is " << dist[i] << endl;
    }

    // Bellman-Ford algorithm
    if (bellmanFord(0, graph, dist)) {
        cout << "Bellman-Ford algorithm:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Distance from 0 to " << i << " is " << dist[i] << endl;
        }
    } else {
        cout << "Graph contains a negative weight cycle" << endl;
    }

    // SPFA algorithm
    if (spfa(0, graph, dist)) {
        cout << "SPFA algorithm:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Distance from 0 to " << i << " is " << dist[i] << endl;
        }
    } else {
        cout << "Graph contains a negative weight cycle" << endl;
    }

    // Floyd-Warshall algorithm
    vector<vector<int>> all_pairs_dist;
    floydWarshall(graph, all_pairs_dist);
    cout << "Floyd-Warshall algorithm:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (all_pairs_dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << all_pairs_dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}