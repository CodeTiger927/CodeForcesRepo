using namespace std;

#include <iostream>
#include <vector>

#define MAXN 300005
#define MOD 998244353

int N,dp[MAXN],par[MAXN],h[MAXN],ans[MAXN];
vector<int> edges[MAXN];

bool dfs(int v,int k) {
	dp[v] = 0;
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		par[u] = v;
		if(!dfs(u,k)) return false;
	}
	if(dp[v] % k == 0) {
		if(v) dp[par[v]]++;
		return true;
	}
	return (dp[v] + !!v) % k == 0;
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) edges[i].clear();
	h[1] = 1;
	for(int i = 0;i < N - 1;++i) {
		h[1] = (h[1] << 1) % MOD;
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 2;i <= N;++i) {
		h[i] = 0;
		if((N - 1) % i != 0) continue;
		h[i] = dfs(0,i);
	}
	for(int i = N;i >= 1;--i) {
		ans[i] = h[i];
		for(int j = 2 * i;j <= N;j += i) {
			ans[i] = (MOD + ans[i] - ans[j]) % MOD;
		}
	}
	for(int i = 1;i <= N;++i) {
		cout << ans[i] << " \n"[i == N];
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}