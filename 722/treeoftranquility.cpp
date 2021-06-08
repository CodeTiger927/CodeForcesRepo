using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 300005

int N,tin[MAXN],tout[MAXN],par[MAXN],par2[MAXN],t,ans;
vector<int> edges[MAXN],edges2[MAXN];
set<pair<int,int>> s;

int add(int v) {
	auto p = s.lower_bound({tin[v],v});
	if(p != s.end() && tout[p -> second] <= tout[v]) return -2;
	if(p == s.begin()) return -1;
	p--;
	int res = p -> second;
	if(tout[v] > tout[res]) return -1;
	s.erase(p);
	return res;
}

void dfs(int v) {
	tin[v] = t++;
	for(int u : edges2[v]) {
		if(u == par2[v]) continue;
		dfs(u);
	}
	tout[v] = t;
}

void dfs2(int v) {
	int res = add(v);
	if(res != -2) s.insert({tin[v],v});
	ans = max(ans,(int)s.size());
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		dfs2(u);
	}
	if(res != -2) {
		s.erase({tin[v],v});
		if(res != -1) s.insert({tin[res],res});
	}
	return;
}

void solve() {
	cin >> N;
	ans = 0;
	s.clear();
	t = 0;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
		edges2[i].clear();
	}
	for(int i = 1;i < N;++i) {
		cin >> par[i];
		par[i]--;
		edges[i].push_back(par[i]);
		edges[par[i]].push_back(i);
	}
	for(int i = 1;i < N;++i) {
		cin >> par2[i];
		par2[i]--;
		edges2[i].push_back(par2[i]);
		edges2[par2[i]].push_back(i);
	}
	dfs(0);
	dfs2(0);
	cout << ans << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}