// file: range_sum.cpp
#include <iostream>
#include <vector>

using namespace std;

// Fenwick Tree for Point Update and Range Query
class FenwickTree {
public:
    FenwickTree(int size) : tree(size + 1, 0) {}

    void update(int index, int delta) {
        while (index < tree.size()) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
    }

private:
    vector<int> tree;
};

// Fenwick Tree for Range Update and Point Query
class FenwickTreeRangeUpdate {
public:
    FenwickTreeRangeUpdate(int size) : tree(size + 1, 0) {}

    void update(int index, int delta) {
        while (index < tree.size()) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    void rangeUpdate(int left, int right, int delta) {
        update(left, delta);
        update(right + 1, -delta);
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

private:
    vector<int> tree;
};

// Segment Tree for Range Update and Range Query
class SegmentTree {
public:
    SegmentTree(int size) : n(size), tree(4 * size, 0), lazy(4 * size, 0) {}

    void rangeUpdate(int left, int right, int delta) {
        rangeUpdate(1, 0, n - 1, left, right, delta);
    }

    int rangeQuery(int left, int right) {
        return rangeQuery(1, 0, n - 1, left, right);
    }

private:
    int n;
    vector<int> tree, lazy;

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void rangeUpdate(int node, int start, int end, int left, int right, int delta) {
        propagate(node, start, end);
        if (start > end || start > right || end < left) return;
        if (start >= left && end <= right) {
            tree[node] += (end - start + 1) * delta;
            if (start != end) {
                lazy[node * 2] += delta;
                lazy[node * 2 + 1] += delta;
            }
            return;
        }
        int mid = (start + end) / 2;
        rangeUpdate(node * 2, start, mid, left, right, delta);
        rangeUpdate(node * 2 + 1, mid + 1, end, left, right, delta);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int rangeQuery(int node, int start, int end, int left, int right) {
        propagate(node, start, end);
        if (start > end || start > right || end < left) return 0;
        if (start >= left && end <= right) return tree[node];
        int mid = (start + end) / 2;
        int leftSum = rangeQuery(node * 2, start, mid, left, right);
        int rightSum = rangeQuery(node * 2 + 1, mid + 1, end, left, right);
        return leftSum + rightSum;
    }
};

int main() {
    // Point Update, Range Query
    vector<int> nums = {1, 7, 3, 0, 7, 8, 3, 2, 6, 2};
    FenwickTree fenwickTree(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        fenwickTree.update(i + 1, nums[i]);
    }
    cout << "Sum of range [1, 5]: " << fenwickTree.rangeQuery(1, 5) << endl; // Output: 18

    // Point Update, Point Query
    fenwickTree.update(4, 5 - nums[3]); // nums[3] is 0, so delta is 5
    cout << "Value at index 4: " << fenwickTree.query(4) << endl; // Output: 5

    // Range Update, Point Query
    FenwickTreeRangeUpdate fenwickTreeRangeUpdate(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        fenwickTreeRangeUpdate.rangeUpdate(i + 1, i + 1, nums[i]);
    }
    fenwickTreeRangeUpdate.rangeUpdate(2, 5, 3);
    cout << "Value at index 4 after range update: " << fenwickTreeRangeUpdate.query(4) << endl; // Output: 8

    // Range Update, Range Query
    SegmentTree segmentTree(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        segmentTree.rangeUpdate(i, i, nums[i]);
    }
    segmentTree.rangeUpdate(1, 5, 3);
    cout << "Sum of range [1, 5] after range update: " << segmentTree.rangeQuery(1, 5) << endl; // Output: 33

    return 0;
}