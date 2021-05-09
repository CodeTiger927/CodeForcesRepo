using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN 20
#define MAXK 262144

int N,M,dp[MAXN][MAXN][MAXK],sum[MAXN],need[MAXN],ans[MAXN];
vector<int> edges[MAXN];
bool vis[MAXN],use[MAXN][MAXN][MAXK];
vector<int> order;

void dfs(int v,bool flag) {
	if(vis[v]) return;
	vis[v] = true;
	for(int u : edges[v]) {
		dfs(u,flag);
	}
	if(flag) {
		order.push_back(v);
	}
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		sum[a] += c;
		sum[b] -= c;
		edges[a].push_back(b);
	}
	for(int i = 0;i < N;++i) {
		dfs(i,true);
	}
	reverse(order.begin(),order.end());
	for(int i = 0;i < N;++i) {
		memset(vis,0,sizeof(vis));
		dfs(i,false);
		for(int j = 0;j < N;++j) {
			if(i == j) continue;
			if(vis[j]) need[i] |= (1 << j);
		}
	}
	// dp[i][j][k] = in total we've used i numbers, we are at order[j], bitmask k has been used
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j <= N;++j) {
			for(int k = 0;k < (1 << N);++k) {
				dp[i][j][k] = 1e9;
			}
		}
	}
	dp[0][0][0] = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j <= N;++j) {
			for(int k = 0;k < (1 << N);++k) {
				if(j == N) {
					if(dp[i + 1][0][k] > dp[i][j][k]) {
						dp[i + 1][0][k] = dp[i][j][k];
						use[i + 1][0][k] = false;
					}
					continue;
				}
				int v = order[j];
				int add = sum[v] * i;
				// If I don't add here, skip
				if(dp[i][j + 1][k] > dp[i][j][k]) {
					dp[i][j + 1][k] = dp[i][j][k];
					use[i][j + 1][k] = false;
				}
				// If I do add here
				if((k & (1 << v)) == 0 && ((need[v] & k) == need[v])) {
					int nk = k | (1 << v);
					if(dp[i][j + 1][nk] > dp[i][j][k]) {
						dp[i][j + 1][nk] = dp[i][j][k] + add;
						use[i][j + 1][nk] = true;
					}
				}
			}
		}
	}
	int a = N;
	int b = 0;
	int c = (1 << N) - 1;
	while(c) {
		if(b == 0) {
			a--;
			b = N;
		}else{
			if(use[a][b][c]) {
				ans[order[b - 1]] = a;
				c ^= (1 << order[b - 1]);
			}
			b--;
		}
	}
	for(int i = 0;i < N;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
}