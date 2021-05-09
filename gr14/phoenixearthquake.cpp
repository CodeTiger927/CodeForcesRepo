using namespace std;

#include <iostream>
#include <vector>

#define MAXN 300005

int N,M,X,root[MAXN];
long long f[MAXN];
vector<pair<int,int>> edges[MAXN],all;
vector<int> ans;

int findR(int x) {
	return (x == root[x] ? x : root[x] = findR(root[x]));
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b || f[a] + f[b] < X) return;
	if(edges[a].size() < edges[b].size()) swap(a,b);
	for(auto v : edges[b]) edges[a].push_back(v);
	edges[b].clear();
	root[b] = a;
	f[a] += f[b] - X;
	return;
}

bool sameR(int a,int b) {
	return findR(a) == findR(b);
}

int main() {
	cin >> N >> M >> X;
	long long sum = 0;
	for(int i = 0;i < N;++i) {
		cin >> f[i];
		sum += f[i];
		root[i] = i;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		all.push_back({a,b});
		edges[a].push_back({b,i});
		edges[b].push_back({a,i});
	}
	if(sum < 1ll * (N - 1) * X) {
		cout << "NO" << endl;
		return 0;
	}
	for(int i = 0;i < N;++i) {
		if(f[findR(i)] < X) continue;
		for(int j = findR(i);edges[j].size() && f[j] >= X;j = findR(j)) {
			pair<int,int> v = edges[j].back();
			edges[j].pop_back();
			if(sameR(j,v.first) || f[j] + f[findR(v.first)] < X) continue;
			merge(j,v.first);
			ans.push_back(v.second + 1);
		}
	}
	for(int i = 0;i < M;++i) {
		if(sameR(all[i].first,all[i].second)) continue;
		merge(all[i].first,all[i].second);
		ans.push_back(i + 1);
	}
	cout << "YES" << endl;
	for(int i : ans) cout << i << endl;
	return 0;
}