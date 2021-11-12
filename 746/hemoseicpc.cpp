using namespace std;

#include <iostream>
#include <vector>

#define MAXN 1005

int N,tot,par[MAXN],ma;
vector<int> edges[MAXN],ord;

int ask(int x) {
	cout << "? " << x;
	for(int i = 0;i < x;++i) cout << " " << ord[i];
	cout << endl;
	int res;
	cin >> res;
	return res;
}

void dfs(int v) {
	ord.push_back(v);
	for(auto u : edges[v]) {
		if(u == par[v]) continue;
		par[u] = v;
		dfs(u);
	}
	return;
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
	dfs(1);
	int l = 1;
	int r = N;
	ma = ask(N);
	while(r - l > 1) {
		int m = (l + r) >> 1;
		if(ask(m) != ma) {
			l = m;
		}else{
			r = m;
		}
	}
	cout << "! " << ord[l] << " " << par[ord[l]] << endl;
	return 0;
}