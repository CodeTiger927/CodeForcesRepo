using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,root[MAXN],A[MAXN],B[MAXN];
vector<int> comp[MAXN],edges[MAXN];
vector<pair<int,bool>> pos[MAXN];
bool vis[MAXN];

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	if(comp[a].size() < comp[b].size()) swap(a,b);
	root[b] = a;
	for(int x : comp[b]) comp[a].push_back(x);
	return;
}

void dfs(int v,bool t,int& odd,int& even,vector<int>& o,vector<int>& e) {
	if(vis[v]) return;
	vis[v] = true;
	(t ? odd : even) += comp[v].size();
	(t ? o : e).push_back(v);
	for(auto u : edges[v]) {
		dfs(u,!t,odd,even,o,e);
	}
	return;
}

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		root[i] = i;
		comp[i] = {i};
		pos[i].clear();
		edges[i].clear();
		vis[i] = false;
	}
	for(int i = 1;i <= N;++i) {
		cin >> A[i];
		pos[A[i]].push_back({i,0});
	}
	for(int i = 1;i <= N;++i) {
		cin >> B[i];
		pos[B[i]].push_back({i,1});
	}
	for(int i = 1;i <= N;++i) {
		if(pos[i].size() != 2) {
			cout << -1 << endl;
			return;
		}
		if(pos[i][0].second != pos[i][1].second) {
			merge(pos[i][0].first,pos[i][1].first);
		}
	}
	for(int i = 1;i <= N;++i) {
		if(pos[i][0].second == pos[i][1].second) {
			edges[findR(pos[i][0].first)].push_back(findR(pos[i][1].first));
			edges[findR(pos[i][1].first)].push_back(findR(pos[i][0].first));
		}
	}
	long long ans = 0;
	vector<int> vans;
	for(int i = 1;i <= N;++i) {
		if(i != findR(i) || vis[i]) continue;
		int odd = 0;
		int even = 0;
		vector<int> e,o;
		dfs(i,0,odd,even,o,e);
		if(odd < even) {
			for(int x : o) vans.push_back(x);
		}else{
			for(int x : e) vans.push_back(x);
		}
		ans += min(odd,even);
	}
	cout << ans << "\n";
	for(int c : vans) {
		for(int v : comp[c]) {
			cout << v << " ";
		}
	}
	cout << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}