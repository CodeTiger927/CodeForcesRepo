using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 300005

// Disjoint Union Find DSU
int root[MAXN],szDSU[MAXN];
vector<int> comps[MAXN],edges[MAXN];

// Call this first please
void initDSU() {
	for(int i = 0;i < MAXN;++i) {
		root[i] = i;
		szDSU[i] = 1;
		comps[i].push_back(i);
	}
}

int findR(int x) {
	if(root[x] != root[root[x]]) {
		root[x] = findR(root[x]);
	}
	return root[x];
}

void mergeDSU(int a,int b) {
	int aR = findR(a);
	int bR = findR(b);
	if(aR == bR) return;
	if(szDSU[aR] > szDSU[bR]) swap(aR,bR);
	szDSU[bR] += szDSU[aR];
	for(int i : comps[aR]) {
		comps[bR].push_back(i);
	}
	root[aR] = bR;
	return;
}

bool checkDSU(int a,int b) {
	return (findR(a) == findR(b));
}

int N,M,par[MAXN],pre[MAXN],nxt[MAXN],used[MAXN];
vector<int> order;
bool exist[MAXN],flag,flag2;

void examine(int n) {
	int curR = findR(n);
	comps[curR].clear();
	int cnt = 0;
	while(pre[n] != n) {
		n = pre[n];
		cnt++;
		if(cnt > szDSU[curR]) {
			flag2 = true;
			return;
		}
	}
	comps[curR].push_back(n);
	exist[n] = true;
	if(findR(par[n]) == curR) flag2 = true;
	while(nxt[n] != n) {
		n = nxt[n];
		exist[n] = true;
		comps[curR].push_back(n);
		if(findR(par[n]) == curR && !exist[par[n]]) flag2 = true;
	}
	return;
}

void topoSort(int cur) {
	used[cur] = 1;
	for(int u : edges[cur]) {
		if(u == cur) continue;
		if(used[u] == 0) {
			topoSort(u);
		}else if(used[u] == 1) {
			flag = true;
		}
		if(flag) return;
	}
	order.push_back(cur);
	used[cur] = 2;
	return;
}

bool topoSort() {
	for(int i = 1;i <= N;++i) {
		if(i != findR(i)) continue;
		if(!used[i]) {
			topoSort(i);
			if(flag) return false;
		}
	}
	reverse(order.begin(),order.end());
	return true;
}

int main() {
	initDSU();
	cin >> N >> M;
	for(int i = 1;i <= N;++i) {
		cin >> par[i];
		edges[par[i]].push_back(i);
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		if(nxt[a] || pre[b]) {
			cout << 0 << endl;
			return 0;
		}
		nxt[a] = b;
		pre[b] = a;
		mergeDSU(a,b);
	}
	for(int i = 1;i <= N;++i) {
		if(!nxt[i]) nxt[i] = i;
		if(!pre[i]) pre[i] = i;
	}
	for(int i = 1;i <= N;++i) {
		if(findR(i) != i) continue;
		for(int j : comps[i]) {
			if(i == j) continue;
			for(int v : edges[j]) {
				edges[i].push_back(v);
			}
		}
		for(int& j : edges[i]) {
			j = findR(j);
		}
		sort(edges[i].begin(),edges[i].end());
		edges[i].erase(unique(edges[i].begin(),edges[i].end()),edges[i].end());
		examine(i);
	}
	if(flag2 || !topoSort()) {
		cout << 0 << endl;
		return 0;
	}
	for(int i : order) {
		for(int j : comps[i]) {
			cout << j << " ";
		}
	}
	cout << endl;
	return 0;
}