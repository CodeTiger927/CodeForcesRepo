using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 200005

int N,M,deg[MAXN];
vector<int> edges1[MAXN],edges2[MAXN];
bool vis1[MAXN],vis2[MAXN];

void dfs(int u,vector<int> edges[MAXN],bool vis[MAXN]) {
	if(vis[u]) return;
	vis[u] = true;
	for(int v : edges[u]) dfs(v,edges,vis);
	return;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges1[a].push_back(b);
		edges2[b].push_back(a);
		deg[b]++;
	}
	int cnt = 0;
	queue<int> q;
	for(int i = 0;i < N;++i) {
		if(!deg[i]) q.push(i);
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		cnt++;
		for(int v : edges1[u]) if(--deg[v] == 0) q.push(v);
	}
	if(cnt != N) {
		cout << -1 << endl;
		return 0;
	}
	string ans = "";
	cnt = 0;
	for(int i = 0;i < N;++i) {
		if(!vis1[i] && !vis2[i]) {
			ans += 'A';
			cnt++;
		}else{
			ans += 'E';
		}
		dfs(i,edges1,vis1);dfs(i,edges2,vis2);
	}
	cout << cnt << " " << ans << endl;
	return 0;
}