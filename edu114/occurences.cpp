using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAXN 300005
#define MOD 998244353

int N,M,K,cnt[MAXN],dp[MAXN];
bool bad[MAXN],vis[MAXN];
vector<int> v[MAXN],nxt[MAXN],pre[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		int c;
		cin >> c;
		v[i].resize(c);
		for(int j = 0;j < c;++j) {
			cin >> v[i][j];
			v[i][j]--;
			if(j > 0) {
				nxt[v[i][j - 1]].push_back(v[i][j]);
				pre[v[i][j]].push_back(v[i][j - 1]);
			}
		}
		if(set<int>(v[i].begin(),v[i].end()).size() != v[i].size()) {
			for(int j : v[i]) bad[j] = true;
		}
	}
	for(int i = 0;i < K;++i) {
		sort(nxt[i].begin(),nxt[i].end());
		sort(pre[i].begin(),pre[i].end());
		nxt[i].erase(unique(nxt[i].begin(),nxt[i].end()),nxt[i].end());
		pre[i].erase(unique(pre[i].begin(),pre[i].end()),pre[i].end());
	}
	for(int i = 0;i < K;++i) {
		if(vis[i]) continue;
		vis[i] = true;
		vector<int> comp = {i};
		for(int j = 0;j < comp.size();++j) {
			int v = comp[j];
			for(int u : nxt[v]) {
				if(!vis[u]) {
					vis[u] = true;
					comp.push_back(u);
				}
			}
			for(int u : pre[v]) {
				if(!vis[u]) {
					vis[u] = true;
					comp.push_back(u);
				}
			}
		}
		bool b = false;
		int beg = 0;
		for(int v : comp) {
			if(pre[v].empty()) beg++;
			if(pre[v].size() > 1 || nxt[v].size() > 1) b = true;
		}
		b |= (beg == 0);
		if(!b) cnt[comp.size()]++;
	}
	vector<int> v;
	for(int i = 1;i <= K;++i) {
		if(cnt[i]) v.push_back(i);
	}
	dp[0] = 1;
	for(int i = 1;i <= M;++i) {
		for(int j : v) {
			if(j <= i) dp[i] += 1ll * dp[i - j] * cnt[j] % MOD;
			if(dp[i] >= MOD) dp[i] -= MOD;
		}
	}
	cout << dp[M] << endl;
	return 0;
}