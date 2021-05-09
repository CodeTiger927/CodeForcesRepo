using namespace std;

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,dp[MAXN],arr[MAXN],tin[MAXN],tout[MAXN],parent[MAXN],euler[MAXN],t,ans;
set<pair<int,int>> g;
vector<int> edges[MAXN];
map<int,vector<int>> mv,times;

void dfs(int cur) {
	tin[cur] = t;
	euler[t++] = cur;
	for(int i : edges[cur]) {
		if(i == parent[cur]) continue;
		parent[i] = cur;
		dfs(i);
	}
	tout[cur] = t - 1;
	return;
}

void check(int cur) {
	int total = 0;
	for(int i : edges[cur]) {
		if(i == parent[cur]) continue;
		int cnt = upper_bound(times[arr[cur]].begin(),times[arr[cur]].end(),tout[i]) - lower_bound(times[arr[cur]].begin(),times[arr[cur]].end(),tin[i]);
		if(cnt) {
			g.insert({cur,i});
		}
		total += cnt;
	}
	if(times[arr[cur]].size() - total - 1) {
		g.insert({cur,parent[cur]});

	}
	return;
}

void init(int cur) {
	for(int i : edges[cur]) {
		if(i == parent[cur]) continue;
		init(i);
		dp[cur] += dp[i] + g.count({i,cur});
	}
	return;
}

void dfs2(int cur) {
	if(dp[cur] == g.size()) {
		ans++;
	}
	for(int i : edges[cur]){
		if(i == parent[cur]) continue;
		dp[cur] -= dp[i];
		dp[cur] -= g.count({i,cur});
		dp[i] += dp[cur];
		dp[i] += g.count({cur,i});

		dfs2(i);

		dp[i] -= g.count({cur,i});
		dp[i] -= dp[cur];
		dp[cur] += g.count({i,cur});
		dp[cur] += dp[i];
	}
	return;
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		mv[arr[i]].push_back(i);
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(0);
	for(auto i : mv) {
		for(auto j : i.second) {
			times[i.first].push_back(tin[j]);
		}
		sort(times[i.first].begin(),times[i.first].end());
		for(auto j : i.second) {
			check(j);
		}
	}
	init(0);
	dfs2(0);
	cout << ans << endl;
	return 0;
}