using namespace std;

#include <iostream>
#include <array>
#include <algorithm>

#define MAXN 100005

int N,M,root[MAXN];
array<long long,3> edges[MAXN];
long long tot,sum[MAXN],res[MAXN];

int findR(int a) {
	return root[a] == root[root[a]] ? root[a] : root[a] = findR(root[a]);
}

void merge(int a,int b,long long w) {
	a = findR(a);
	b = findR(b);
	// cout << a << " " << b << " " << w << endl;
	if(a == b) return;
	res[a] = max(min(res[a],w - (tot - sum[a])),min(res[b],w - (tot - sum[b])));
	sum[a] += sum[b];
	root[b] = a;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		root[i] = i;
		cin >> sum[i];
		tot += sum[i];
		res[i] = 1e18;
	}
	for(int i = 0;i < M;++i) {
		cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
		edges[i][1]--;edges[i][2]--;
	}
	sort(edges,edges + M);
	for(int i = M - 1;i >= 0;--i) {
		merge(edges[i][1],edges[i][2],edges[i][0]);
	}
	long long ans = res[findR(0)];
	cout << (ans <= 0 ? -1 : ans) << endl;
	return 0;
}