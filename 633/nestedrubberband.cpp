using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 100005

struct Two {
	int f,s;
	Two(int v): f(v), s(v) {}
	void update(int v) {
		if(v > f) {
			s = f;
			f = v;
		}else if(v > s) {
			s = v;
		}
		return;
	}
};

int N,dps[MAXN],dpt[MAXN],par[MAXN];
vector<int> edges[MAXN];

int skip(int);
int take(int);

int dfs(int v) {
	Two bestskip(0),both(0);
	int res = edges[v].size();
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		par[u] = v;
		res = max(res,dfs(u));
		bestskip.update(skip(u));
		both.update(max(skip(u),take(u)));
	}
	res = max(res,1 + bestskip.f + bestskip.s);
	res = max(res,(int)edges[v].size() - 1 + both.f);
	res = max(res,(int)edges[v].size() - 2 + both.f + both.s);
	return res;
}

int skip(int v) {
	if(~dps[v]) return dps[v];
	int c = edges[v].size() - (!!v);
	int res = c;
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		res = max(res,c - 1 + take(u));
		res = max(res,c - 1 + skip(u));
	}
	return dps[v] = res;
}

int take(int v) {
	if(~dpt[v]) return dpt[v];
	int res = 1;
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		res = max(res,1 + skip(u));
	}
	return dpt[v] = res;
}

int main() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	memset(dps,-1,sizeof(dps));
	memset(dpt,-1,sizeof(dpt));
	cout << dfs(0) << endl;;
	return 0;
}