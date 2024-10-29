#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

long long solve(vector<int> aPsum, vector<int> bPsum, int s, int g) {
    int winningCondition = (g + 1) / 2;
    int target = aPsum[s] + winningCondition;
    // cout << "aPsum[s]: " << aPsum[s] << " winningCondition: " << winningCondition << " target: " << target << endl;
    auto it = lower_bound(aPsum.begin() + s, aPsum.begin() + s + g + 1, target);
    if(it <= aPsum.begin() + s + g) {
        // cout << "s: " << s << " g: " << g << " target: " << target << " it: " << it - aPsum.begin() << endl;
        // cout << "A!! " << it - aPsum.begin() - s << endl;
        return it - aPsum.begin() - s;
    }
    else {
        target = bPsum[s] + winningCondition;
        // cout << "bPsum[s]: " << bPsum[s] << " winningCondition: " << winningCondition << " target: " << target << endl;
        it = lower_bound(bPsum.begin() + s, bPsum.begin() + s + g + 1, target);
        // cout << "s: " << s << " g: " << g << " target: " << target << " it: " << it - bPsum.begin() << endl;
        // cout << "B!! " << it - bPsum.begin() - s << endl;
        return it - bPsum.begin() - s;
    }
}

int main() {
    fastio;

    int T;
    cin >> T;

    while(T--) {
        int N, M;
        cin >> N >> M;
        string W;
        cin >> W;
        W += W;
        vector<int> aPsum(N*2+1);
        vector<int> bPsum(N*2+1);
        for(int i=1; i<=N*2; ++i) {
            aPsum[i] = aPsum[i-1] + (W[i-1] == 'A');
            bPsum[i] = bPsum[i-1] + (W[i-1] == 'B');
        }
        // aPsum, bPsum 출력
        // for(int i=0; i<=N*2; ++i) cout << aPsum[i] << ' ';
        // cout << '\n';
        // for(int i=0; i<=N*2; ++i) cout << bPsum[i] << ' ';
        // cout << '\n';

        long long ans = 0;
        for(int i=0; i<M; ++i) {
            int s, g;
            cin >> s >> g;
            ans += solve(aPsum, bPsum, s-1, g);
        }
        cout << ans << '\n';
    }

    return 0;
}