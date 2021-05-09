using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005
#define MAXK 45

int N,K,K2,dp[MAXN][MAXK],parent[MAXN];
vector<int> edges[MAXN];

void dfs(int v) {
	for(int u : edges[v]) {
		if(u == parent[v]) continue;
		parent[u] = v;
		dfs(u);
		for(int i = 0;i < K2;++i) {
			dp[v][(i + 1) % K2] ^= dp[u][i];
		}
	}
	return;
}

void dfs2(int v) {
	for(int u : edges[v]) {
		if(u == parent[v]) continue;
		int tmp[MAXK];
		for(int i = 0;i < K2;++i) {
			tmp[i] = dp[u][i];
		}
		for(int i = 0;i < K2;++i) {
			dp[u][(i + 2) % K2] ^= tmp[i] ^ dp[v][(i + 1) % K2];
		}
		dfs2(u);
	}
	return;
}

int main() {
	cin >> N >> K;
	K2 = 2 * K;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 0;i < N;++i) {
		cin >> dp[i][0];
	}
	dfs(0);
	dfs2(0);
	for(int i = 0;i < N;++i) {
		int cur = 0;
		for(int j = K;j < K2;++j) {
			cur ^= dp[i][j];
		}
		cout << !!cur << " ";
	}
	cout << endl;
	return 0;
}