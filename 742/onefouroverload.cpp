using namespace std;

#include <iostream>
#include <vector>

#define MAXN 505

int N,M,comp[MAXN][MAXN],c,flip[MAXN * MAXN],ans[MAXN][MAXN];
char arr[MAXN][MAXN];
vector<int> edges[MAXN * MAXN];

int dx[8] = {0,1,0,-1,1,1,-1,-1};
int dy[8] = {1,0,-1,0,1,-1,1,-1};

void dfs(int i,int j) {
	for(int k = 0;k < 8;++k) {
		int nx = dx[k] + i;
		int ny = dy[k] + j;
		if(arr[nx][ny] != '.' || comp[nx][ny]) continue;
		comp[nx][ny] = comp[i][j];
		dfs(nx,ny);
	}
	return;
}

void dfs2(int v) {
	for(int u : edges[v]) {
		if(flip[u]) continue;
		flip[u] = 3 - flip[v];
	}
	return;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i <= N + 1;++i) {
		for(int j = 0;j <= M + 1;++j) {
			if(i == 0 || i == N + 1 || j == 0 || j == M + 1) {
				arr[i][j] = '-';
			}else{
				cin >> arr[i][j];
			}
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			int cur = 0;
			if(arr[i][j] != 'X') continue;
			for(int k = 0;k < 4;++k) {
				if(arr[i + dx[k]][j + dy[k]] == '.') cur++;
			}
			if(cur & 1) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			if(arr[i][j] != '.' || comp[i][j]) continue;
			comp[i][j] = ++c;
			dfs(i,j);
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			if(arr[i][j] != '.') continue;
			for(int k = 0;k < 4;++k) {
				int x = i + dx[k];
				int y = j + dy[k];
				if(arr[x][y] == 'X') {
					int nx = i + 2 * dx[k];
					int ny = j + 2 * dy[k];
					if(arr[nx][ny] == '.') {
						edges[comp[i][j]].push_back(comp[nx][ny]);
						edges[comp[nx][ny]].push_back(comp[i][j]);
					}
				}
			}
		}
	}
	for(int i = 1;i <= c;++i) {
		if(flip[i]) continue;
		flip[i] = 1;
		dfs2(i);
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			if(arr[i][j] == '.') ans[i][j] = ((i & 1) ^ (flip[comp[i][j]] - 1)) ? 1 : 4;
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			if(arr[i][j] == 'X') {
				for(int k = 0;k < 4;++k) {
					if(arr[i + dx[k]][j + dy[k]] == '.') ans[i][j] += ans[i + dx[k]][j + dy[k]];
				}
			}
		}
	}
	cout << "YES" << endl;
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			cout << ans[i][j] << " \n"[j == M];
		}
	}
	return 0;
}