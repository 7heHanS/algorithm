#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> trees;
int N, M;

bool Check(int mid) {
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        if (trees[i] > mid) {
            sum += trees[i] - mid;
        }
    }
    // lower_bound 조건
    return sum >= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int lo = 0, hi = (int)1e9 + 1;
    cin >> N >> M;
    trees.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> trees[i];
    }

    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (Check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << lo << endl;

    return 0;
}