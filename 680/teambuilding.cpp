using namespace std;

#include <iostream>
#include <stack>
#include <map>
#include <vector>

#define MAXN 1000005

int N,M,K,root[MAXN],rnk[MAXN],col[MAXN];
bool isBi[MAXN];
map<pair<int,int>,vector<pair<int,int>>> edges;

stack<pair<pair<int,int>,pair<int,int>>> rollback;

int findR(int x) {
	return x == root[x] ? x : findR(root[x]);
}

void merge(int a,int b) {
	int aR = findR(a);
	int bR = findR(b);
	if(aR == bR) return;
	if(rnk[bR] > rnk[aR]) swap(aR,bR);
	rollback.push({{bR,root[bR]},{aR,rnk[aR]}});
	root[bR] = aR;
	rnk[aR] += (rnk[aR] == rnk[bR]);
	return;
}

void rollbackEverything() {
	while(!rollback.empty()) {
		pair<pair<int,int>,pair<int,int>> cur = rollback.top();
		rollback.pop();
		root[cur.first.first] = cur.first.second;
		rnk[cur.second.first] = cur.second.second;
	}
	return;
}

int main() {
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		cin >> col[i];
	}
	for(int i = 0;i < 2 * N;++i) {
		root[i] = i;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(col[a] == col[b]) {
			if(isBi[col[a]]) continue;
			merge(a,b + N);
			merge(b,a + N);
			if(findR(a) == findR(b)) {
				isBi[col[a]] = true;
				K--;
			}
		}else{
			if(col[a] > col[b]) swap(a,b);
			edges[{col[a],col[b]}].push_back({a,b});
		}
	}
	while(!rollback.empty()) rollback.pop();
	long long ans = 1ll * K * (K - 1) / 2;
	for(auto p : edges) {
		if(isBi[p.first.first] || isBi[p.first.second]) continue;
		for(auto e : p.second) {
			merge(e.first,e.second + N);
			merge(e.first + N,e.second);
			if(findR(e.first) == findR(e.second)) {
				ans--;
				break;
			}
		}
		rollbackEverything();
	}
	cout << ans << endl;
	return 0;
}