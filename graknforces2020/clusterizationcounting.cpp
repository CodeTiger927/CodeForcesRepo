using namespace std;

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

#define MAXN 1505
#define MOD 998244353

int N,d[MAXN][MAXN],root[MAXN],sz[MAXN],cnt[MAXN];
long long dp[MAXN][MAXN],tmp[MAXN];
vector<array<int,3>> edges;

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(sz[a] < sz[b]) swap(a,b);
	if(a != b) {
		for(int i = 1;i <= sz[a] + sz[b];++i) {
			tmp[i] = 0;
		}
		for(int i = 1;i <= sz[a];++i) {
			for(int j = 1;j <= sz[b];++j) {
				tmp[i + j] += dp[a][i] * dp[b][j] % MOD;
				if(tmp[i + j] >= MOD) tmp[i + j] -= MOD;
			}
		}
		for(int i = 1;i <= sz[a] + sz[b];++i) {
			dp[a][i] = tmp[i];
		}
		root[b] = a;
		sz[a] += sz[b];
		cnt[a] += cnt[b];
	}
	cnt[a]++;
	if(cnt[a] == sz[a] * sz[a]) {
		dp[a][1]++;
		if(dp[a][1] >= MOD) dp[a][1] -= MOD;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for(int i = 0;i < N;++i) {
		sz[i] = 1;
		root[i] = i;
		for(int j = 0;j < N;++j) {
			cin >> d[i][j];
			edges.push_back({d[i][j],i,j});
		}
	}
	sort(edges.begin(),edges.end());
	for(int i = 0;i < N * N;++i) {
		merge(edges[i][1],edges[i][2]);
	}
	for(int i = 1;i <= N;++i) {
		cout << dp[findR(0)][i] << " ";
	}
	cout << endl;
	return 0;
}