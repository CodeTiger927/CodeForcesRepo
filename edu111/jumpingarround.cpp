using namespace std;

#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <cstring>

#define MAXN 200005
#define MAXM 1000005

int N,Q,S,D,arr[MAXN],ind[MAXM],root[MAXN],dist[MAXN],cnt;
vector<int> comps[MAXN];
vector<pair<int,int>> edges[MAXN];

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

bool merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return false;
	if(comps[a].size() < comps[b].size()) swap(a,b);
	root[b] = a;
	for(int x : comps[b]) comps[a].push_back(x);
	return true;
}

void dfs(int v) {
	for(auto [w,u] : edges[v]) {
		if(~dist[u]) continue;
		dist[u] = max(dist[v],w);
		dfs(u);
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q >> S >> D;
	memset(dist,-1,sizeof(dist));
	cnt = N;
	set<int> s;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		ind[arr[i]] = i;
		root[i] = i;
		comps[i] = {i};
		s.insert(arr[i]);
	}
	while(cnt > 1) {
		// cout << "Hello " << cnt << endl;
		vector<array<int,3>> v;
		for(int i = 1;i <= N;++i) {
			if(root[i] != i) continue;
			for(int x : comps[i]) {
				s.erase(arr[x]);
			}
			array<int,3> e = {1000000000,-1,-1};
			for(int x : comps[i]) {
				for(int d : {D,-D}) {
					auto it = s.lower_bound(arr[x] + d);
					if(it != s.end()) {
						e = min(e,{abs(abs(arr[x] - *it) - D),x,ind[*it]});
					}
					if(it != s.begin()) {
						e = min(e,{abs(abs(arr[x] - *--it) - D),x,ind[*it]});
					}
				}
			}
			v.push_back(e);
			for(int x : comps[i]) {
				s.insert(arr[x]);
			}
		}
		for(auto [a,b,c] : v) {
			if(merge(b,c)) {
				cnt--;
				edges[b].push_back({a,c});
				edges[c].push_back({a,b});
			}
		}
	}
	dist[S] = 0;
	dfs(S);
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		cout << (b >= dist[a] ? "YES" : "NO") << endl;
	}
	return 0;
}