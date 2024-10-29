#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

// Returns sum of arr[0..index]. This function assumes
// that the array is preprocessed and partial sums of
// array elements are stored in BITree[]
int getSum(int BITree[], int index)
{
    int sum = 0; // Initialize result

    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse ancestors of BITree[index]
    while (index > 0) {
        // Add current element of BITree to sum
        sum += BITree[index];

        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return sum;
}

// Updates a node in Binary Index Tree (BITree) at given
// index in BITree. The given value 'val' is added to
// BITree[i] and all of its ancestors in tree.
void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse all ancestors and add 'val'
    while (index <= n) {
        // Add 'val' to current node of BI Tree
        BITree[index] += val;

        // Update index to that of parent in update View
        index += index & (-index);
    }
}

// Returns the sum of array from [0, x]
int sum(int x, int BITTree1[], int BITTree2[])
{
    return (getSum(BITTree1, x) * x) - getSum(BITTree2, x);
}

void updateRange(int BITTree1[], int BITTree2[], int n,
                int val, int l, int r)
{
    // Update Both the Binary Index Trees
    // As discussed in the article

    // Update BIT1
    updateBIT(BITTree1, n, l, val);
    updateBIT(BITTree1, n, r + 1, -val);

    // Update BIT2
    updateBIT(BITTree2, n, l, val * (l - 1));
    updateBIT(BITTree2, n, r + 1, -val * r);
}

int rangeSum(int l, int r, int BITTree1[], int BITTree2[])
{
    // Find sum from [0,r] then subtract sum
    // from [0,l-1] in order to find sum from
    // [l,r]
    return sum(r, BITTree1, BITTree2)
        - sum(l - 1, BITTree1, BITTree2);
}

void constructBITrees(int n, int BITTree1[], int BITTree2[], const vector<int>& initialValues)
{
    // Create and initialize BITree[] as 0
    for (int i = 1; i <= n; i++) {
        BITTree1[i] = 0;
        BITTree2[i] = 0;
    }

    // Initialize BITrees with initialValues
    for (int i = 0; i < initialValues.size(); i++) {
        updateBIT(BITTree1, n, i, initialValues[i]);
        updateBIT(BITTree2, n, i, initialValues[i]);
    }
}

// Driver code
int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--) {
        int n, m;
		int base = 0, dir = 0;
        cin >> n >> m;

        vector<int> initialValues(n);
        for (int i = 0; i < n; ++i) {
            cin >> initialValues[i];
        }

        // Construct two BIT
        int *BITTree1 = new int[n + 1];
        int *BITTree2 = new int[n + 1];

        // Initialize BITrees with the input array
        constructBITrees(n, BITTree1, BITTree2, initialValues);

		vector<int> s(m);
		vector<int> x(m);
		vector<int> y(m);
		vector<int> output;

		for(int i = 0; i < m; i++) cin >> s[i];
		for(int i = 0; i < m; i++) cin >> x[i];
		for(int i = 0; i < m; i++) cin >> y[i];

        for(int i = 0; i < m; i++) {
            int type = s[i];

            if(type == 1) {
				// dir == 0 이면 base를 x[i]만큼 증가시키고, dir == 1이면 base를 x[i]만큼 감소시킨다.
				// base가 n을 넘어가면 0부터 시작하고, 0보다 작아지면 n-1부터 시작한다.
				if(dir == 0) {
					base = (base + x[i]) % n;
				}
				else {
					base = (base - x[i] + n) % n;
				}
			}
			else if(type == 2) {
				// dir == 0 이면 base를 x[i]만큼 감소시키고, dir == 1이면 base를 x[i]만큼 증가시킨다.
				// base가 n을 넘어가면 0부터 시작하고, 0보다 작아지면 n-1부터 시작한다.
				if(dir == 0) {
					base = (base - x[i] + n) % n;
				}
				else {
					base = (base + x[i]) % n;
				}
			}
			else if(type == 3) {
				// dir이 0이면 dir을 1로, 1이면 0으로 바꾼다.
				dir = 1 - dir;
			}
			else if (type == 4) {
				// dir==0 이면, base부터 base + x[i] - 1 까지 y[i]만큼 증기시킨다.
				// base + x[i] - 1이 n을 넘어가면 base to n-1까지, 그리고 0부터 (base + x[i] - 1)%n 까지 증가시킨다.
				// dir==1 이면, base - x[i] + 1 부터 base 까지 y[i]만큼 증가시킨다.
				// base - x[i] + 1이 0보다 작아지면 0 to base, 그리고 (base - x[i] + 1 + n)%n to n-1 까지 증가시킨다.
				if(dir == 0) {
					if(base + x[i] - 1 < n) {
						updateRange(BITTree1, BITTree2, n, y[i], base, base + x[i] - 1);
					}
					else {
						updateRange(BITTree1, BITTree2, n, y[i], base, n - 1);
						updateRange(BITTree1, BITTree2, n, y[i], 0, (base + x[i] - 1) % n);
					}
				}
				else {
					if(base - x[i] + 1 >= 0) {
						updateRange(BITTree1, BITTree2, n, y[i], base - x[i] + 1, base);
					}
					else {
						updateRange(BITTree1, BITTree2, n, y[i], 0, base);
						updateRange(BITTree1, BITTree2, n, y[i], (base - x[i] + 1 + n) % n, n - 1);
					}
				}
            } else if (type == 5) {
				int result = 0;
				// type == 4 일 때와 같은 방식으로 rangeSum을 구한다.
				if(dir == 0) {
					if(base + x[i] - 1 < n) {
						result = rangeSum(base, base + x[i] - 1, BITTree1, BITTree2);
						output.push_back(result);
					}
					else {
						result = rangeSum(base, n - 1, BITTree1, BITTree2) + rangeSum(0, (base + x[i] - 1) % n, BITTree1, BITTree2);
						output.push_back(result);
					}
				}
				else {
					if(base - x[i] + 1 >= 0) {
						result = rangeSum(base - x[i] + 1, base, BITTree1, BITTree2);
						output.push_back(result);
					}
					else {
						result = rangeSum(0, base, BITTree1, BITTree2) + rangeSum((base - x[i] + 1 + n) % n, n - 1, BITTree1, BITTree2);
						output.push_back(result);
					}
				}
            }
        }

		for(int i = 0; i < output.size(); i++) {
			cout << output[i] << " ";
		}
		cout << "\n";
        // Clean up
        delete[] BITTree1;
        delete[] BITTree2;
    }

    return 0;
}