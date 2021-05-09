using namespace std;

#include <iostream>
#include <queue>

#define MAXN 605
#define MAXM 200005
#define INF 1e15

int N,M,Q;
long long dist[MAXN][MAXN],dist2[MAXN][MAXN],w[MAXM];
vector<pair<int,int>> edges[MAXN],queries[MAXN],all;
bool mark[MAXM];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b >> w[i];
		a--;b--;
		edges[a].push_back({b,i});
		edges[b].push_back({a,i});
		dist[a][b] = dist[b][a] = w[i];
		all.push_back({a,b});
	}
	for(int k = 0;k < N;++k) {
		for(int i = 0;i < N;++i) {
			for(int j = 0;j < N;++j) {
				dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
			} 
		}
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int a,b,l;
		cin >> a >> b >> l;
		a--;b--;
		if(dist[a][b] == INF) continue;
		queries[a].push_back({b,l});
		dist2[a][b] = -l;
	}
	for(int k = 0;k < N;++k) {
		for(int i = 0;i < N;++i) {
			for(int j = 0;j < N;++j) {
				dist2[i][j] = min(dist2[i][j],dist2[i][k] + dist[k][j]);
			} 
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < all.size();++j) {
			int v = all[j].first;
			int u = all[j].second;
			long long wei = w[j];
			if(dist2[i][v] <= -wei - dist[u][i] || dist2[i][u] <= -wei - dist[v][i]) {
				mark[j] = true;
			}
		}
	}
	int ans = 0;
	for(int i = 0;i < M;++i) {
		ans += mark[i];
	}
	cout << ans << endl;
	return 0;
}