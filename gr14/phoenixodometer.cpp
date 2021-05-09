using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,M,Q,vis[MAXN];
long long scc[MAXN],loop[MAXN],len[MAXN];
vector<pair<int,long long>> edges[MAXN],edges2[MAXN];
vector<int> ord;

void dfs(int v) {
	vis[v] = 1;
	for(auto e : edges[v]) {
		if(vis[e.first]) continue;
		dfs(e.first);
	}
	ord.push_back(v);
	return;
}

void dfs2(int v) {
	vis[v] = 2;
	for(auto e : edges2[v]) {
		if(vis[e.first] != 2) {
			scc[e.first] = scc[v];
			len[e.first] = len[v] + e.second;
			dfs2(e.first);
		}else if(scc[e.first] == scc[v]) {
			loop[scc[v]] = __gcd(loop[scc[v]],llabs(len[v] - len[e.first] + e.second));
		}
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		long long c;
		cin >> a >> b >> c;
		a--;b--;
		edges[a].push_back({b,c});
		edges2[b].push_back({a,c});
	}
	for(int i = 0;i < N;++i) {
		if(!vis[i]) dfs(i);
	}
	reverse(ord.begin(),ord.end());
	for(int i : ord) {
		if(vis[i] == 2) continue;
		scc[i] = i;
		dfs2(i);
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int v;
		long long s,t;
		cin >> v >> s >> t;
		v--;
		long long g = loop[scc[v]];
		if(s % __gcd(g,t) == 0) {
			cout << "YES\n";
		}else{
			cout << "NO\n";
		}
	}
	return 0;
}