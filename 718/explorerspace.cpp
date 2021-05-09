using namespace std;

#include <iostream>
#include <vector>

#define MAXN 505
#define MAXK 15

int N,M,K;
long long dp[MAXN][MAXN][MAXK];
vector<pair<long long,pair<int,int>>> edges[MAXN][MAXN];

int main() {
	cin >> N >> M >> K;
	if(K % 2 == 1) {
		for(int i = 0;i < N;++i) {
			for(int j = 0;j < M;++j) {
				cout << -1 << " ";
			}
			cout << endl;
		}
		return 0;
	}
	K >>= 1;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M - 1;++j) {
			long long cur;
			cin >> cur;
			edges[i][j].push_back({cur,{i,j + 1}});
			edges[i][j + 1].push_back({cur,{i,j}});
		}
	}
	for(int i = 0;i < N - 1;++i) {
		for(int j = 0;j < M;++j) {
			long long cur;
			cin >> cur;
			edges[i][j].push_back({cur,{i + 1,j}});
			edges[i + 1][j].push_back({cur,{i,j}});
		}
	}
	for(int i = 1;i <= K;++i) {
		for(int j = 0;j < N;++j) {
			for(int k = 0;k < M;++k) {
				dp[j][k][i] = 1e16;
				for(auto m : edges[j][k]) {
					dp[j][k][i] = min(dp[j][k][i],m.first + dp[m.second.first][m.second.second][i - 1]);
				}
			}
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cout << dp[i][j][K] * 2 << " ";
		}
		cout << endl;
	}
	return 0;

}