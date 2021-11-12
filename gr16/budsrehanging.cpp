using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,par[MAXN],ans;
vector<int> edges[MAXN],v;
bool leaf[MAXN],bud[MAXN];

void dfs(int v) {
	int cnt = 0;
	leaf[v] = bud[v] = true;
	if(v == 1) leaf[v] = false;
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		par[u] = v;
		dfs(u);
		if(!leaf[u] && !bud[u]) {
			bud[v] = false;
		}
		if(leaf[u]) cnt++;
		if(!bud[u]) leaf[v] = false;
	}
	if(leaf[v]) {
		bud[v] = false;
	}
	if(bud[v]) {
		// cout << v << " " << cnt << endl;
		ans += max(0,cnt - 1);
	}

	return;
}

void solve() {
	cin >> N;
	ans = 1;
	for(int i = 0;i <= N;++i) {
		edges[i].clear();
		par[i] = leaf[i] = bud[i] = 0;
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1);
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}