using namespace std;

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#define MAXN 200005

int ans,N,depth[MAXN],parent[MAXN],cnt[MAXN];
vector<int> edges[MAXN];
stack<int> s;

void dfs(int cur) {
	if(cur != 0 && edges[cur].size() == 1) {
		depth[cur] = 1;
		return;
	}
	vector<int> v;
	for(int u : edges[cur]) {
		if(u == parent[cur]) continue;
		cnt[cur]++;
		parent[u] = cur;
		dfs(u);
		v.push_back(depth[u]);
	}
	sort(v.begin(),v.end());
	if(v.size() > 1) {
		if(cur == 0) {
			ans = max({ans,v[v.size() - 1],v[v.size() - 2] + 1});
		}else{
			ans = max(ans,v[v.size() - 1] + 1);
		}
	}
	depth[cur] = v[0] + 1;
	ans = max(ans,v[0]);
	return;
}

void solve() {
	ans = 0;
	while(!s.empty()) s.pop();
	cin >> N;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}