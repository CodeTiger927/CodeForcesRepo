using namespace std;

#include <iostream>
#include <vector>

#define MAXN 300005
#define MAXM 500005

int N,M,u[MAXM],v[MAXM],w[MAXM],root[MAXN],par[MAXN][20],bit[MAXN],tin[MAXN],tout[MAXN],dep[MAXN],t;
vector<pair<int,bool>> edges[MAXN];
bool ans[MAXM],val[MAXN];

void upd(int x,int v) {
	x++;
	while(x < MAXN) {
		bit[x] += v;
		x += x & -x;
	}
	return;
}

int get(int x) {
	x++;
	int res = 0;
	while(x) {
		res += bit[x];
		x -= x & -x;
	}
	return res;
}

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

inline void mark(int u) {
	upd(tin[u],1);
	upd(tout[u],-1);
	return;
}

bool merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return false;
	root[b] = a;
	return true;
}

void dfs(int v) {
	tin[v] = t++;
	for(auto [u,w] : edges[v]) {
		if(u == par[v][0]) continue;
		par[u][0] = v;
		val[u] = val[v] ^ w;
		dep[u] = dep[v] + 1;
		dfs(u);
	}
	tout[v] = t;
	return;
}

int LCA(int u,int v) {
	if(dep[u] < dep[v]) swap(u,v);
	int d = dep[u] - dep[v];
	for(int i = 19;i >= 0;--i) {
		if(d & (1 << i)) u = par[u][i];
	}
	if(u == v) return u;
	for(int i = 19;i >= 0;--i) {
		if(par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		par[i][0] = root[i] = i;
	}
	for(int i = 0;i < M;++i) {
		cin >> u[i] >> v[i] >> w[i];
		u[i]--;v[i]--;
		if(merge(u[i],v[i])) {
			ans[i] = true;
			edges[u[i]].push_back({v[i],w[i]});
			edges[v[i]].push_back({u[i],w[i]});
		}
	}
	for(int i = 0;i < N;++i) {
		if(i == 0 || !tin[i]) dfs(i);
	}
	for(int i = 1;i < 20;++i) {
		for(int j = 0;j < N;++j) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
	for(int i = 0;i < M;++i) {
		if(ans[i]) {
			cout << "YES" << "\n";
			continue;
		}
		int c = val[u[i]] ^ val[v[i]] ^ w[i];
		int l = LCA(u[i],v[i]);
		int sum = get(tin[u[i]]) + get(tin[v[i]]) - 2 * get(tin[l]);
		if(!c || sum) {
			cout << "NO" << "\n";
		}else{
			cout << "YES" << "\n";
			for(int j = v[i];j != l;j = par[j][0]) mark(j);
			for(int j = u[i];j != l;j = par[j][0]) mark(j);
		}
	}
	return 0;
}