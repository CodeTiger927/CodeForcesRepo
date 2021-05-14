using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,M,root[MAXN],sz[MAXN];
long long a[MAXN],b[MAXN];
vector<pair<int,int>> edges;

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a,b);
	root[b] = a;
	sz[a] += sz[b];
	return;
}

bool same(int a,int b) {
	return findR(a) == findR(b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
	}
	for(int i = 0;i < M;++i) {
		cin >> b[i];
	}
	for(int i = 0;i < N + M;++i) {
		sz[i] = 1;
		root[i] = i;
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		int c;
		cin >> c;
		for(int j = 0;j < c;++j) {
			int cur;
			cin >> cur;
			cur--;
			edges.push_back({i,cur + N});
			ans += a[i] + b[cur];
		}
	}
	sort(edges.begin(),edges.end(),[&](pair<int,int> x,pair<int,int> y) {return (a[x.first] + b[x.second - N]) > (a[y.first] + b[y.second - N]);});
	for(int i = 0;i < edges.size();++i) {
		int x = edges[i].first;
		int y = edges[i].second;
		if(same(x,y)) continue;
		merge(x,y);
		ans -= a[x] + b[y - N];
	}
	cout << ans << endl;
	return 0;
}