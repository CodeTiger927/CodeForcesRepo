using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 1000005

int N,K,arr[MAXN],par[MAXN],dp[MAXN],pref[MAXN],tot;
vector<int> edges[MAXN];

void dfs(int v) {
	int sum = 0;
	pref[v] = arr[v];
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		par[u] = v;
		dfs(u);
		pref[v] ^= pref[u];
		sum += dp[u];
	}
	dp[v] = max((int)(pref[v] == tot),sum);
	return;
}

void solve() {
	tot = 0;
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		dp[i] = 0;
		cin >> arr[i];
		tot ^= arr[i];
		edges[i].clear();
		par[i] = 0;
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	if(tot == 0) {
		cout << "YES" << endl;
		return;
	}
	if(K == 2) {
		cout << "NO" << endl;
		return;
	}
	if(dp[0] >= 2) {
		cout << "YES" << endl;
		return;
	}
	for(int i = 1;i < N;++i) {
		if(dp[i] && !pref[i]) {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}