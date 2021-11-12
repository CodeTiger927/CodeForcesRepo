using namespace std;

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

#define MAXN 1005
#define MAXK 45

int N,M,K,Q,a[MAXN][MAXN],dist[MAXK][MAXN][MAXN];
vector<pair<int,int>> cells[MAXK];
bool vis[MAXK];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> a[i][j];
			cells[a[i][j]].push_back({i,j});
		}
	}
	memset(dist,-1,sizeof(dist));
	for(int i = 1;i <= K;++i) {
		memset(vis,0,sizeof(vis));
		queue<pair<int,int>> q;
		for(auto [x,y] : cells[i]) {
			dist[i][x][y] = 0;
			q.push({x,y});
		}
		while(!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			if(!vis[a[x][y]]) {
				vis[a[x][y]] = true;
				for(auto [nx,ny] : cells[a[x][y]]) {
					if(!~dist[i][nx][ny]) {
						dist[i][nx][ny] = dist[i][x][y] + 1;
						q.push({nx,ny});
					}
				}
			}
			for(int k = 0;k < 4;++k) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if(nx >= 0 && nx < N && ny >= 0 && ny < M && !~dist[i][nx][ny]) {
					dist[i][nx][ny] = dist[i][x][y] + 1;
					q.push({nx,ny});
				} 
			}
		}
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		int x,y,w,z;
		cin >> x >> y >> w >> z;
		x--;y--;w--;z--;
		int ans = abs(x - w) + abs(y - z);
		for(int j = 1;j <= K;++j) ans = min(ans,dist[j][x][y] + dist[j][w][z] + 1);
		cout << ans << endl;
	}
	return 0;
}