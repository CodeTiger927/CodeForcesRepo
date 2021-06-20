using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 1005

int N,dep[MAXN],par[MAXN];
vector<int> edges[MAXN],levels[MAXN];

pair<int,int> qry(vector<int> nodes) {
	cout << "? " << nodes.size();
	for(int v : nodes) cout << " " << v + 1;
	cout << endl;
	int a,b;
	cin >> a >> b;
	return {a - 1,b};
}

int dfs(int u) {
	int maxD = dep[u];
	levels[dep[u]].push_back(u);
	for(int v : edges[u]) {
		if(v == par[u]) continue;
		par[v] = u;
		dep[v] = dep[u] + 1;
		maxD = max(maxD,dfs(v));
	}
	return maxD;
}

void solve() {
	cin >> N;
	vector<int> all;
	for(int i = 0;i < MAXN;++i) {
		levels[i].clear();
		edges[i].clear();
	}
	for(int i = 0;i < N;++i) {
		all.push_back(i);
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	pair<int,int> res = qry(all);
	par[res.first] = res.first;
	dep[res.first] = 0;
	int l = res.second / 2;
	int r = min(res.second,dfs(res.first)) + 1;
	pair<int,int> firstNode = res;
	while(r - l > 1) {
		int m = (l + r) >> 1;
		pair<int,int> cur = qry(levels[m]);
		if(cur.second == res.second) {
			l = m;
			firstNode = cur;
		}else{
			r = m;
		}
	}
	if(dep[firstNode.first] != l) firstNode = qry(levels[l]);
	for(int i = 0;i < N;++i) {
		levels[i].clear();
	}
	par[firstNode.first] = firstNode.first;
	dep[firstNode.first] = 0;
	dfs(firstNode.first);
	int secondNode = qry(levels[res.second]).first;
	cout << "! " << firstNode.first + 1 << " " << secondNode + 1 << endl;
	string status;
	cin >> status;
	if(status != "Correct") exit(0);
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}