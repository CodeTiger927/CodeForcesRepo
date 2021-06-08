using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 605

int N,M,d[MAXN][MAXN],dist[MAXN];
bool vis[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	memset(d,63,sizeof(d));
	for(int i = 0;i < M;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		d[a][b] = min(d[a][b],c);
	}
	for(int i = 0;i < N;++i) {
		memset(dist,63,sizeof(dist));
		memset(vis,0,sizeof(vis));
		for(int j = 0;j < N;++j) {
			dist[j] = min(dist[j],d[i][j]);
		}
		while(true) {
			int v = -1;
			for(int x = 0;x < N;++x) {
				if(!vis[x]) {
					if(v == -1 || dist[x] < dist[v]) v = x;
				}
			}
			if(v == -1) break;
			vis[v] = true;
			dist[(v + 1) % N] = min(dist[(v + 1) % N],dist[v] + 1);
			for(int u = 0;u < N;++u) {
				dist[(u + dist[v]) % N] = min(dist[(u + dist[v]) % N],dist[v] + d[v][u]);
			}
		}
		for(int j = 0;j < N;++j) {
			if(i == j) {
				cout << "0 ";
			}else{
				cout << dist[j] << " ";
			}
		}
		cout << endl;
	}
	return 0;
}