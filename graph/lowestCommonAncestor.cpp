#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 단순 재귀 방식
// Time Complexity: O(N), Space Complexity: O(N)
// 각 쿼리 별로 O(N) 시간 복잡도
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

// 희소 테이블 방식
// Time Complexity: O(NlogN), Space Complexity: O(NlogN)
// 여러 쿼리를 처리할 때 유용 (쿼리 별로 O(logN) 시간 복잡도)
class LCA {
    vector<vector<int>> up;
    vector<int> depth;
    int LOG;

public:
    LCA(TreeNode* root, int n) {
        LOG = log2(n) + 1;
        up.assign(n, vector<int>(LOG));
        depth.assign(n, 0);
        dfs(root, root->val);
    }

    void dfs(TreeNode* node, int parent) {
        up[node->val][0] = parent;
        for (int i = 1; i < LOG; ++i) {
            up[node->val][i] = up[up[node->val][i - 1]][i - 1];
        }
        if (node->left) {
            depth[node->left->val] = depth[node->val] + 1;
            dfs(node->left, node->val);
        }
        if (node->right) {
            depth[node->right->val] = depth[node->val] + 1;
            dfs(node->right, node->val);
        }
    }

    int query(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; ++i) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* p = root->left; // 5
    TreeNode* q = root->left->right->right; // 4

    // 단순 재귀 방식
    TreeNode* lca_recursive = lowestCommonAncestor(root, p, q);
    if (lca_recursive) {
        cout << "LCA (Recursive) of " << p->val << " and " << q->val << " is " << lca_recursive->val << endl;
    } else {
        cout << "LCA not found (Recursive)" << endl;
    }

    // 희소 테이블 방식
    int n = 9; // Number of nodes
    LCA lca_sparse(root, n);

    int ancestor = lca_sparse.query(p->val, q->val);
    cout << "LCA (Sparse Table) of " << p->val << " and " << q->val << " is " << ancestor << endl;

    return 0;
}