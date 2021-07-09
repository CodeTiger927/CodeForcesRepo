using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

int N,M,par[MAXN];
vector<int> edges[MAXN];
vector<pair<int,int>> ans;

void dfs(int v,int val) {
	ans.push_back({v,val});
	int i = 0;
	int cur = val;
	for(int u : edges[v]) {
		if(u == par[v]) continue;
		if(++cur == M) {
			cur = val - (edges[v].size() - (!!par[v])) + i;
			ans.push_back({v,cur - 1});
		}
		par[u] = v;
		dfs(u,cur);
		ans.push_back({v,cur});
		i++;
	}
	if(cur != val - 1) {
		ans.push_back({v,val - 1});
	}
	return;
}

int main() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 1;i <= N;++i) {
		M = max(M,(int)edges[i].size() + 1);
	}

	dfs(1,0);
	ans.pop_back();
	cout << ans.size() << endl;
	for(auto p : ans) {
		cout << p.first << " " << p.second << endl;
	}
	return 0;
}