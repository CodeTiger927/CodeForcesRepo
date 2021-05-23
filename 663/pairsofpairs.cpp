using namespace std;

#include <iostream>
#include <vector>

#define MAXN 500005

bool vis[MAXN];
int N,M,par[MAXN],dep[MAXN];
vector<int> edges[MAXN],depths[MAXN];

void dfs(int v) {
	vis[v] = true;
	depths[dep[v]].push_back(v);
	for(int u : edges[v]) {
		if(vis[u]) continue;
		par[u] = v;
		dep[u] = dep[v] + 1;
		dfs(u);
	}
	return;
}

void solve() {
	cin >> N >> M;
	for(int i = 0;i <= N;++i) {
		edges[i].clear();
		depths[i].clear();
		vis[i] = false;
		dep[i] = 0;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 0;i < N;++i) {
		if(vis[i]) continue;
		par[i] = i;
		dep[i] = 1;
		dfs(i);
	}
	for(int i = 0;i < N;++i) {
		if(dep[i] >= (N + 1) >> 1) {
			cout << "PATH" << "\n";
			int x = i;
			cout << dep[x] << "\n";
			while(x != par[x]) {
				cout << x + 1 << " ";
				x = par[x];
			}
			cout << x + 1 << "\n";
			return;
		}
	}
	cout << "PAIRING" << "\n";
	vector<pair<int,int>> v;
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < (int)depths[i].size() - 1;j += 2) {
			v.push_back({depths[i][j] + 1,depths[i][j + 1] + 1});
		}
	}
	cout << v.size() << "\n";
	for(auto p : v) cout << p.first << " " << p.second << "\n";
	return;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}