// Function List:
// - dfs(const Graph &g, int v)                   : Depth-first search on a graph
// - count_bits(int bits)                         : Count number of set bits in an integer
// - prefix_sum_1d()                              : Build 1D prefix sums on global array 'a'
// - two_pointers()                               : Two-pointer (sliding window) template
// - meguru_binary_search(const vector<int>&, int): Find lower_bound index in sorted vector
// - gcd(LL a, LL b)                              : Compute greatest common divisor
// - lcm(LL a, LL b)                              : Compute least common multiple
// - bit_exhaustive_search(int n)                 : Iterate over all subsets of size n
// - mod_pow(LL base, LL exp, LL mod)             : Fast modular exponentiation (base^exp % mod)
// - is_prime(LL x)                               : Primality check by trial division
// - enumerate_divisors(LL n)                     : List all divisors of n in sorted order
// - prime_factor(LL n)                           : Map of prime factorization of n
// - build_comb()                                 : Precompute combination table C[n][k] % MOD
// - Combination::comb(int n, int k)              : O(1) nCk after precompute
// - lcs()                                        : Compute length of longest common subsequence
// - edit_distance()                              : Compute minimum edit distance between two strings
// - BellmanFord                                  : Negative-cycle detection & shortest paths
// - UnionFind                                    : Disjoint-set (union-find) operations
// - dijkstra(const vector<vector<pair<int,LL>>>&, int)
//                                                : Dijkstra's shortest path algorithm
// - floyd_warshall(vector<vector<LL>>& d)        : Floyd–Warshall all-pairs shortest paths
// - SegTree                                      : Segment tree for range sum queries and point updates
// - FenwickTree                                  : Fenwick (BIT) for prefix sums and point updates

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
using LL  = long long;
using ULL = unsigned long long;

// optional constants
const double EPS = 1e-7;
const double PI  = acos(-1);

// DFS template
using Graph = vector<vector<int>>;
vector<bool> visited;

// Description: Depth-first search on graph g starting from vertex v.
// Input: const Graph& g (adjacency list), int v (start vertex).
// Output: marks reachable nodes in global 'visited'.
void dfs(const Graph &g, int v) {
    visited[v] = true;
    for (int u : g[v]) {
        if (visited[u]) continue;
        dfs(g, u);
    }
}

// Description: Count number of 1-bits in the integer.
// Input: int bits.
// Output: int count of set bits.
int count_bits(int bits) {
    int cnt = 0;
    while (bits) {
        cnt++;
        bits &= bits - 1;
    }
    return cnt;
}

// Syntax analysis
using State = string::const_iterator;

// Prefix sum (1D)
// Description: Build prefix sums for array 'a' into 'acc1'.
// Input: global vector<int> a of size N.
// Output: acc1[i+1] = sum of a[0..i].
vector<int> a(100);
vector<int> acc1(101, 0);
void prefix_sum_1d() {
    for (int i = 0; i < 100; i++) {
        acc1[i+1] = acc1[i] + a[i];
    }
}

// Prefix sum (2D)
// acc[x+1][y+1] = acc[x][y+1] + acc[x+1][y] - acc[x][y] + a[x][y]

// Two pointers (sliding window)
// Description: Demonstrate two-pointer/sliding window template.
// Input/Output: adjusts 'right' to maintain window [left,right).
void two_pointers() {
    int right = 0;
    for (int left = 0; left < 100; ++left) {
        while (right < 100 /* && condition holds if we advance right */) {
            ++right;
        }
        // now [left, right) is maximal valid window
        // process result using (right - left)
        if (right == left) ++right;
    }
}

// Meguru-style binary search
// Description: Find smallest index i where v[i] >= key.
// Input: sorted vector<int> v, int key.
// Output: index OK (0..v.size()).
int meguru_binary_search(const vector<int>& v, int key) {
    int ng = -1, ok = (int)v.size();
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        if (v[mid] >= key) ok = mid;
        else ng = mid;
    }
    return ok;
}

// GCD and LCM
// Description: Compute greatest common divisor.
// Input: LL a, LL b.
// Output: LL gcd(a,b).
LL gcd(LL a, LL b) {
    if (a < b) return gcd(b, a);
    while (b) {
        LL r = a % b;
        a = b; b = r;
    }
    return a;
}
// Description: Compute least common multiple.
// Input: LL a, LL b.
// Output: LL lcm(a,b).
LL lcm(LL a, LL b) {
    return a / gcd(a, b) * b;
}

// Exhaustive bit search
// Description: Iterate over all subsets of size n.
// Input: int n (default 20).
// Output: use bitmask to process each subset.
void bit_exhaustive_search(int n = 20) {
    for (int bit = 0; bit < (1 << n); bit++) {
        for (int i = 0; i < n; i++) {
            if (bit & (1 << i)) {
                // process element i
            }
        }
    }
}

// Fast modular exponentiation
// Description: Compute (base^exp) % mod in O(log exp).
// Input: LL base, LL exp, LL mod.
// Output: LL result.
LL mod_pow(LL base, LL exp, LL mod) {
    LL res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Primality check
// Description: Test if x is prime by trial division.
// Input: LL x.
// Output: bool (true if prime).
bool is_prime(LL x) {
    if (x < 2) return false;
    for (LL i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// Enumerate divisors
// Description: List all divisors of n in sorted order.
// Input: LL n.
// Output: vector<LL> of divisors.
vector<LL> enumerate_divisors(LL n) {
    vector<LL> res;
    for (LL i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

// Prime factorization
// Description: Compute prime factor map of n.
// Input: LL n.
// Output: map<LL,int> {prime->exponent}.
map<LL,int> prime_factor(LL n) {
    map<LL,int> ret;
    for (LL i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ret[i]++;
            n /= i;
        }
    }
    if (n > 1) ret[n]++;
    return ret;
}

// Combination table (n choose k)
// Description: Precompute C[n][k] % MOD up to MAX_C.
// Input: none.
// Output: global C table.
const int MAX_C = 2100;
LL C[MAX_C][MAX_C];
const LL MOD = 1e9+7;
void build_comb() {
    memset(C, 0, sizeof(C));
    C[0][0] = 1;
    for (int i = 1; i < MAX_C; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}

// Combination with precomputed factorials / inverses
// Description: O(1) nCk queries after O(n) precompute.
// Input: int n (max).
// Output: fac, finv, inv arrays; comb(n,k) method.
struct Combination {
    vector<LL> fac, finv, inv;
    Combination(int n): fac(n+1), finv(n+1), inv(n+1) {
        fac[0] = finv[0] = inv[1] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i-1] * i % MOD;
            if (i > 1) inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
            finv[i] = finv[i-1] * inv[i] % MOD;
        }
    }
    // Description: Return C(n,k) % MOD in O(1).
    LL comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * (finv[k] * finv[n-k] % MOD) % MOD;
    }
};

// Longest Common Subsequence
// Input: two strings s, t from stdin.
// Output: length of LCS printed to stdout.
void lcs() {
    fastio;
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (s[i] == t[j]) dp[i+1][j+1] = dp[i][j] + 1;
        else dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
    }
    cout << dp[n][m] << "\n";
}

// Edit distance
// Input: two strings s1, s2 from stdin.
// Output: minimum edit distance printed to stdout.
void edit_distance() {
    fastio;
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (s1[i] == s2[j]) dp[i+1][j+1] = dp[i][j];
        else dp[i+1][j+1] = min({dp[i][j]+1, dp[i][j+1]+1, dp[i+1][j]+1});
    }
    cout << dp[n][m] << "\n";
}

// Bellman-Ford (detect negative cycle & shortest path)
// Input: add_edge(u,v,w) to build edges, then build(s).
// Output: dist[] array and bool false if negative cycle detected.
struct BellmanFord {
    struct Edge { int u,v; LL w; };
    int n; vector<Edge> edges; vector<LL> dist;
    const LL INF = (1LL<<60);
    BellmanFord(int n): n(n), dist(n, INF) {}
    void add_edge(int u,int v,LL w) { edges.push_back({u,v,w}); }
    bool build(int s) {
        dist[s]=0;
        for(int i=0;i<n;i++){
            for(auto &e: edges){
                if(dist[e.u]!=INF && dist[e.u]+e.w<dist[e.v]){
                    dist[e.v]=dist[e.u]+e.w;
                    if(i==n-1) return false; // negative cycle
                }
            }
        }
        return true;
    }
};

// Union-Find (Disjoint Set)
// Input: n elements.
// Output: supports merge(a,b), same(a,b), size(x).
struct UnionFind {
    vector<int> p;
    UnionFind(int n): p(n,-1) {}
    int root(int x){ return p[x]<0?x:p[x]=root(p[x]); }
    bool merge(int a,int b){
        a=root(a); b=root(b);
        if(a==b) return false;
        if(p[a]>p[b]) swap(a,b);
        p[a]+=p[b]; p[b]=a; return true;
    }
    bool same(int a,int b){ return root(a)==root(b); }
    int size(int x){ return -p[root(x)]; }
};

// Dijkstra
// Input: graph g as adjacency list of (v,weight), start s.
// Output: vector<LL> dist of min distances.
vector<LL> dijkstra(const vector<vector<pair<int,LL>>>& g, int s) {
    int n = g.size();
    const LL INF = (1LL<<60);
    vector<LL> dist(n, INF);
    priority_queue<pair<LL,int>, vector<pair<LL,int>>, greater<>> pq;
    dist[s]=0; pq.push({0,s});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto& [v,w]: g[u]){
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

// Warshall–Floyd (Floyd–Warshall)
// Input: distance matrix d with INF for no edge.
// Output: d updated to shortest paths.
bool floyd_warshall(vector<vector<LL>>& d) {
    int n = d.size();
    const LL INF = (1LL<<60);
    for(int k=0;k<n;k++) for(int i=0;i<n;i++){
        if(d[i][k]==INF) continue;
        for(int j=0;j<n;j++){
            if(d[k][j]==INF) continue;
            d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        }
    }
    return true;
}

// Segment Tree
// Description: support point update and range sum query in O(log n).
// Usage: SegTree st(N); st.update(1,0,N-1,idx,val); LL sum = st.query(1,0,N-1,l,r);
struct SegTree {
    int n;
    vector<LL> st;
    SegTree(int _n): n(_n), st(4*_n, 0) {}
    void update(int node, int l, int r, int idx, LL val) {
        if (l == r) {
            st[node] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) update(node<<1, l, mid, idx, val);
        else            update(node<<1|1, mid+1, r, idx, val);
        st[node] = st[node<<1] + st[node<<1|1];
    }
    LL query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[node];
        int mid = (l + r) >> 1;
        return query(node<<1, l, mid, ql, qr)
             + query(node<<1|1, mid+1, r, ql, qr);
    }
};

// Fenwick Tree (Binary Indexed Tree)
// Description: support point update and prefix sum query in O(log n).
// Usage: FenwickTree fw(N); fw.update(idx,val); LL sum = fw.query(idx);
struct FenwickTree {
    int n;
    vector<LL> bit;
    FenwickTree(int _n): n(_n), bit(_n+1, 0) {}
    // add val at position idx (1-indexed)
    void update(int idx, LL val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    // prefix sum [1..idx]
    LL query(int idx) {
        LL s = 0;
        for (; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }
    // range sum [l..r]
    LL range_query(int l, int r) {
        return query(r) - query(l-1);
    }
};