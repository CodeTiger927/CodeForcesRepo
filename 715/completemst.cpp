using namespace std;

#include <iostream>
#include <set>
#include <array>
#include <algorithm>
#include <vector>

#define MAXN 200005

struct DSU {
	// Disjoint Union Find DSU
	int root[MAXN],szDSU[MAXN];

	DSU() {
		initDSU();
	}

	// Call this first please
	void initDSU() {
		for(int i = 0;i < MAXN;++i) {
			root[i] = i;
			szDSU[i] = 1;
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
		root[aR] = bR;
		return;
	}
	
	bool checkDSU(int a,int b) {
		return (findR(a) == findR(b));
	}
} d,d2;

int N,M;
long long com;
set<int> edges[MAXN],ava;
vector<array<int,3>> v;

void dfs(int v) {
	ava.erase(v);
	for(int i = 0;;) {
		auto itr = ava.lower_bound(i);
		if(itr == ava.end()) return;
		i = *itr;
		if(edges[v].find(i) == edges[v].end()) {
			d.mergeDSU(v,i);
			dfs(i);
			com--;
		}
		i++;
	}
}

int main() {
	cin >> N >> M;
	com = 1ll * N * (N - 1) / 2 - M;
	int sum = 0;
	for(int i = 0;i < M;++i) {
		int a,b,w;
		cin >> a >> b >> w;
		a--;b--;
		edges[a].insert(b);
		edges[b].insert(a);
		v.push_back({w,a,b});
		sum ^= w;
	}
	for(int i = 0;i < N;++i) {
		ava.insert(i);
	}
	for(int i = 0;i < N;++i) {
		if(ava.find(i) != ava.end()) dfs(i);
	}
	if(com > 0) sum = 0;
	int must = 0;
	sort(v.begin(),v.end());
	for(array<int,3> e : v) {
		if(d.checkDSU(e[1],e[2])) {
			if(!d2.checkDSU(e[1],e[2])) {
				sum = min(sum,e[0]);
			}
		}else{
			d.mergeDSU(e[1],e[2]);
			d2.mergeDSU(e[1],e[2]);
			must += e[0];
		}
	}
	cout << (must + sum) << endl;
	return 0;
}