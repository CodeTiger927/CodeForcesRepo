using namespace std;

#include <iostream>
#include <vector>

#define MAXN 5005
#define MOD 998244353

int N,K,sz[MAXN],par[MAXN];
vector<int> edges[MAXN];
long long dp[MAXN][MAXN],tmp[MAXN];

void dfs(int cur) {
	sz[cur] = 1;
	dp[cur][0] = 1;
	for(int v : edges[cur]) {
		if(v == par[cur]) continue;
		par[v] = cur;
		dfs(v);
		for(int i = 0;i < sz[cur] + sz[v];++i) {
			tmp[i] = 0;
		}
		for(int i = 0;i < sz[cur];++i) {
			for(int j = 0;j < sz[v];++j) {
				if(i + j + 1 <= K) {
					tmp[max(i,j + 1)] += dp[cur][i] * dp[v][j] % MOD;
					if(tmp[max(i,j + 1)] >= MOD) tmp[max(i,j + 1)] -= MOD;
				}
				if(i <= K && j <= K) {
					tmp[i] += dp[cur][i] * dp[v][j] % MOD;
					if(tmp[i] >= MOD) tmp[i] -= MOD;
				}
		 	}
		}
		sz[cur] += sz[v];
		for(int i = 0;i < sz[cur];++i) {
		 	dp[cur][i] = tmp[i];
		}
	}
	return;
}

int main() {
	cin >> N >> K;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	long long ans = 0;
	for(int i = 0;i < sz[0];++i) {
		ans += dp[0][i];
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return 0;
}