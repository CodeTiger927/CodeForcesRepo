using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,vis[MAXN],dp[MAXN];
vector<int> edges[MAXN];

bool dfs(int v,int p) {
	vis[v] = 1;
	for(int u : edges[v]) {
		if(vis[u] == 1) return true;
		if(vis[u] == 0) {
			if(dfs(u,v)) return true;
		}
	}
	vis[v] = 2;
	return false;
}

void dfs2(int v,int p) {
	if(dp[v]) return;
	dp[v] = 1;
	for(int u : edges[v]) {
		dfs2(u,v);
		dp[v] = max(dp[v],dp[u] + (u > v));
	}
	return;
}

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		edges[i].clear();
		dp[i] = vis[i] = 0;
		int k;
		cin >> k;
		for(int j = 0;j < k;++j) {
			int cur;
			cin >> cur;
			edges[i].push_back(cur);
		}
	}
	for(int i = 1;i <= N;++i) {
		if(vis[i] == 0) {
			if(dfs(i,0)) {
				cout << -1 << endl;
				return;
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= N;++i) {
		if(!dp[i]) dfs2(i,0);
		ans = max(ans,dp[i]);
	}
	cout << ans << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}