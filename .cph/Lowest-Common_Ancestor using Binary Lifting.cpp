#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define max3(a, b, c) max(a, max(b, c))
#define min3(a, b, c) min(a, min(b, c))
#define lcm(a, b) ((a * b) / (__gcd(a, b)))
#define rep(i, n) for (ll i = 0; i < n; i++)
#define REP(i, z, n) for (ll i = z; i <= n; i++)
#define MM 1000000007
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

void dfs(int root, vector<int> children[], vector<bool> &visited, vector<vector<int>> &up, vector<int> &depth)
{
    visited[root] = true;
    for (auto b : children[root])
    {
        if (visited[b] == false)
        {
            depth[b] = depth[root] + 1;
            up[b][0] = root; // a is parent of b
            for (int j = 1; j < 18; j++)
            {
                up[b][j] = up[up[b][j - 1]][j - 1];
            }
            dfs(b, children, visited, up, depth);
        }
    }
}

int get_lca(int a, int b, vector<int> children[], vector<vector<int>> &up, vector<int> &depth ) { 
	if(depth[a] < depth[b]) {
		swap(a, b);
	}
	// 1) Get same depth.
	int k = depth[a] - depth[b];
	for(int j = 18 - 1; j >= 0; j--) {
		if(k & (1 << j)) {
			a = up[a][j]; // parent of a
		}
	}
	// 2) if b was ancestor of a then now a==b
	if(a == b) {
		return a;
	}
	// 3) move both a and b with powers of two
	for(int j = 18 - 1; j >= 0; j--) {
		if(up[a][j] != up[b][j]) {
			a = up[a][j];
			b = up[b][j];
		}
	}
	return up[a][0];
}

void solve()
{
    int n;
    cin >> n;
    vector<int> children[n + 1];
    vector<vector<int>> up(n + 1, vector<int>(18, 0));
    vector<int> depth(n + 1, 0);
    vector<bool> visited(n + 1, false);
    for (int v = 0; v < n - 1; v++) // n-1 edges
    {
        int edge1, edge2;
        cin >> edge1 >> edge2;
        children[edge1].push_back(edge2);
        children[edge2].push_back(edge1);
    }
    dfs(0, children, visited, up, depth);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        int lca=  get_lca(a, b, children, up, depth);
        cout << lca << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int testcase = 1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
    cout << endl;
    return 0;
}
