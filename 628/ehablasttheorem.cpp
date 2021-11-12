using namespace std;

#include <iostream>
#include <vector>
#include <math.h>

#define MAXN 200005

int N,M,par[MAXN],d[MAXN];
vector<int> edges[MAXN],edges2[MAXN],in;
bool block[MAXN];

void dfs(int v) {
	for(auto u : edges[v]) {
		if(par[u]) {
			edges2[v].push_back(u);
			continue;
		}
		d[u] = d[v] + 1;
		par[u] = v;
		dfs(u);
	}
	if(!block[v]) {
		for(int u : edges[v]) block[u] = true;
		in.push_back(v);
	}
	return;
}

int main() {
	cin >> N >> M;
	int sq = ceil(sqrt(N));
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	par[1] = 1;
	dfs(1);
	vector<int> v;
	for(int i = 1;i <= N;++i) {
		for(int j : edges2[i]) {
			if(d[i] - d[j] + 1 >= sq) {
				cout << 2 << endl;
				cout << (d[i] - d[j] + 1) << endl;
				for(int x = i;x != j;x = par[x]) {
					cout << x << " ";
				}
				cout << j << endl;
				return 0;
			}
		}
	}
	cout << 1 << endl;
	for(int i = 0;i < sq;++i) {
		cout << in[i] << " \n"[i == sq - 1];
	}
}