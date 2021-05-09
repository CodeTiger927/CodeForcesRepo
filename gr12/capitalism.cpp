using namespace std;

#include <iostream>

#define MAXN 205
#define MAXM 2005
#define INF 1e9

int N,M,u[MAXM],v[MAXM],b[MAXM],dist[MAXN][MAXN];

int main() {
	cin >> N >> M;
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= N;++j) {
			if(i == j) continue;
			dist[i][j] = INF;
		}
	}
	for(int i = 0;i < M;++i) {
		cin >> u[i] >> v[i] >> b[i];
		dist[u[i]][v[i]] = 1;
		dist[v[i]][u[i]] = 1 - 2 * b[i];
	}
	for(int k = 1;k <= N;++k) {
		for(int i = 1;i <= N;++i) {
			for(int j = 1;j <= N;++j) {
				dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
				if(dist[i][j] < -INF) {
					cout << "NO" << endl;
					return 0;
				}
			}
		}
	}
	pair<int,int> best = {0,0};
	for(int i = 1;i <= N;++i) {
		if(dist[i][i] < 0) {
			cout << "NO" << endl;
			return 0;
		}
		for(int j = 1;j <= N;++j) {
			best = max(best,{dist[i][j],i});
		}
	}
	for(int i = 0;i < M;++i) {
		if(dist[best.second][u[i]] == dist[best.second][v[i]]) {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	cout << best.first << endl;
	for(int i = 1;i <= N;++i) {
		cout << dist[best.second][i] << " ";
	}
	cout << endl;
	return 0;
}