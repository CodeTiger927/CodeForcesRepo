using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAXN 200005
#define INF 1e9

int N,M,dist[MAXN],dist2[MAXN];
vector<int> edges[MAXN];
bool visited[MAXN];

void dfs(int cur) {
	visited[cur] = true;
	dist2[cur] = dist[cur];
	for(int i = 0;i < edges[cur].size();++i) {
		int nxt = edges[cur][i];
		if(!visited[nxt] && dist[cur] < dist[nxt]) {
			dfs(nxt);
		}
		if(dist[cur] < dist[nxt]) {
			dist2[cur] = min(dist2[cur],dist2[nxt]);
		}else{
			dist2[cur] = min(dist2[cur],dist[nxt]);
		}
	}
	return;
}

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
	}
	memset(dist,0,sizeof(dist));
	queue<int> q;
	q.push(0);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int i = 0;i < edges[cur].size();++i) {
			int nxt = edges[cur][i];
			if(nxt == 0 || dist[nxt]) continue;
			dist[nxt] = dist[cur] + 1;
			q.push(nxt);
		}
	}
	memset(visited,0,sizeof(visited));
	dfs(0);
	for(int i = 0;i < N;++i) {
		cout << dist2[i] << " ";
	}
	cout << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}