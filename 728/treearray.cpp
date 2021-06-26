using namespace std;

#include <iostream>
#include <vector>

#define MAXN 205
#define MOD 1000000007

int N,dep[MAXN],par[MAXN][9];
long long dp[MAXN][MAXN],inv2 = 500000004;
vector<int> edges[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

void preCompSparseMatrix() {
	for(int i = 1;i < 9;i++) {
		for(int j = 0;j < N;j++) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
}

int LCA(int u,int v) {
	if(dep[v] < dep[u]) return LCA(v,u);

	int dif = dep[v] - dep[u];
	for(int i = 0;i < 9;i++) {
		if((dif >> i) & 1) {
			v = par[v][i];
		}
	}

	if(u == v) {
		return u;
	}

	for(int i = 8;i >= 0;i--) {
		if(par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}

	return par[u][0];
}

void dfs(int v) {
	for(int u : edges[v]) {
		if(u == par[v][0]) continue;
		par[u][0] = v;
		dep[u] = dep[v] + 1;
		dfs(u);
	}
	return;
}

int main() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			if(i == 0) {
				dp[i][j] = 1;
			}else if(j == 0) {
				dp[i][j] = 0;
			}else{
				dp[i][j] = inv2 * (dp[i - 1][j] + dp[i][j - 1]) % MOD;
			}
		}
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		par[i][0] = i;
		dep[i] = 0;
		dfs(i);
		preCompSparseMatrix();
		for(int v = 0;v < N;++v) {
			for(int u = 0;u < N;++u) {
				if(v == u) continue;
				int l = LCA(u,v);
				ans += dp[dep[v] - dep[l]][dep[u] - dep[l]] * (v > u) % MOD;
				if(ans >= MOD) ans -= MOD;
			}
		}
	}
	ans = ans * inv(N) % MOD;
	cout << ans << endl;
	return 0;
}