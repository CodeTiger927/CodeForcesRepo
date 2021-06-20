using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 400005
#define MOD 1000000007

int N,a[MAXN],b[MAXN],ma[MAXN];
bool vis[MAXN];

void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	dfs(ma[b[u]]);
}

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> a[i];
		ma[a[i]] = i;
		vis[i] = false;
	}
	for(int i = 1;i <= N;++i) {
		cin >> b[i];
	}
	long long ans = 1;
	for(int i = 1;i <= N;++i) {
		if(vis[i]) continue;
		dfs(i);
		ans <<= 1;
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}