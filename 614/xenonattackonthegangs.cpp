using namespace std;

#include <iostream>
#include <cstring>
#include <vector>

#define MAXN 3005

int N,par[MAXN][MAXN],sub[MAXN][MAXN];
long long dp[MAXN][MAXN];
vector<int> edges[MAXN];

int dfs(int r,int v) {
	sub[r][v] = 1;
	for(int u : edges[v]) {
		if(u == par[r][v]) continue;
		par[r][u] = v;
		sub[r][v] += dfs(r,u);
	}
	return sub[r][v];
}

long long solve(int v,int u) {
	if(u == v) return 0;
	if(~dp[u][v]) return dp[u][v];
	return dp[u][v] = sub[u][v] * sub[v][u] + max(solve(par[v][u],v),solve(u,par[u][v]));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 1;i <= N;++i) dfs(i,i);
	memset(dp,-1,sizeof(dp));
	long long ans = 0;
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= i;++j) {
			ans = max(ans,solve(i,j));
		}
	}
	cout << ans << endl;
}