using namespace std;

#include <iostream>
#include <cstring>
#include <vector>

#define MAXN 2097152

int N,part[MAXN][2];
bool vis[MAXN];
vector<int> ans;
vector<pair<int,int>> edges[MAXN];

void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	for(auto v : edges[u]) {
		if(!vis[v.first]) dfs(v.first);
	}
	return;
}

bool check(int mask) {
	for(int i = 0;i <= mask;++i) {
		edges[i].clear();
		vis[i] = false;
	}
	for(int i = 0;i < N;++i) {
		int u = part[i][0] & mask;
		int v = part[i][1] & mask;
		edges[u].push_back({v,2 * i + 1});
		edges[v].push_back({u,2 * i});
	}

	int num = 0;
	for(int i = 0;i <= mask;++i) {
		if(edges[i].size() & 1) return false;
		if(!vis[i] && edges[i].size() > 0) {
			num++;
			dfs(i);
		}
	}
	return num == 1;
}

void find(int u,int pre = -1) {
	while(edges[u].size()) {
		auto e = edges[u].back();
		edges[u].pop_back();
		if(vis[e.second / 2]) continue;
		vis[e.second / 2] = true;
		find(e.first,e.second);
	}
	if(pre != -1) {
		ans.push_back(pre);
		ans.push_back(pre ^ 1);
	}
}

void retrieve(int mask) {
	memset(vis,0,sizeof(vis));
	for(int i = 0;i <= mask;++i) {
		if(edges[i].size()) {
			find(i);
			break;
		}
	}
	for(int i = 0;i < 2 * N;++i) {
		cout << ans[i] + 1 << " \n"[i == 2 * N - 1];
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> part[i][0] >> part[i][1];
	}
	for(int i = 20;i >= 0;--i) {
		if(check((1 << i) - 1)) {
			cout << i << endl;
			retrieve((1 << i) - 1);
			return 0;
		}
	}
	return 0;
}