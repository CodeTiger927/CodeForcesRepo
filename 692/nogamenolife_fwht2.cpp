using namespace std;

#include <iostream>
#include <set>
#include <vector>

#define MAXN 100005
#define MAXM (1ll << 17)
#define MOD 998244353

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int N,M,dp[MAXN];
long long f[MAXM];
bool vis[MAXN];
vector<int> edges[MAXN];

void dfs(int v) {
	if(vis[v]) return;
	vis[v] = true;
	set<int> s;
	for(int u : edges[v]) {
		dfs(u);
		s.insert(dp[u]);
	}
	for(int x : s) {
		dp[v] += (dp[v] == x);
	}
	f[dp[v]]++;
	return;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
	}
	for(int i = 0;i < N;++i) {
		if(vis[i]) continue;
		dfs(i);
	}
	// FWHT 	
	for(int k = 1;k < MAXM;k <<= 1) {
		for(int i = 0;i < MAXM;i += k << 1) {
			for(int j = 0;j < k;++j) {
				long long x = f[i + j];
				long long y = f[i + j + k];
				f[i + j] = (x + y) % MOD;
				f[i + j + k] = (MOD + x - y) % MOD;
			}
		}
	}
	for(int i = 0;i < MAXM;++i) {
		f[i] = inv(MOD + 1 - (f[i] * inv(N + 1) % MOD));
	}
	// FWHT Inv
	for(int k = 1;k < MAXM;k <<= 1) {
		for(int i = 0;i < MAXM;i += k << 1) {
			for(int j = 0;j < k;++j) {
				long long x = f[i + j];
				long long y = f[i + j + k];
				f[i + j] = (x + y) % MOD;
				f[i + j + k] = (MOD + x - y) % MOD;
			}
		}
	}

	for(int i = 0;i < MAXM;++i) {
		f[i] = f[i] * inv(MAXM) % MOD;
	}

	long long ans = (MOD + 1 - f[0] * inv(N + 1) % MOD) % MOD;

	cout << ans << endl;
	return 0;
}