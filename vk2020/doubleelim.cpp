using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 17

int N,M,dp[MAXN + 1][1 << MAXN][2][2];

int main() {
	cin >> N >> M;
	memset(dp,0xcf,sizeof(dp));
	for(int i = 0;i < (1 << N);++i) {
		dp[0][i][0][0] = 0;
	}
	for(int i = 0;i < M;++i) {
		int x;
		cin >> x;
		x--;
		dp[0][x][1][0] = 0;
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < (1 << (N - i));++j) {
			for(int a1 = 0;a1 < 2;++a1) {
				for(int b1 = 0;b1 < 2;++b1) {
					for(int a2 = 0;a2 < 2;++a2) {
						for(int b2 = 0;b2 < 2;++b2) {
							int x = dp[i - 1][j << 1][a1][b1] + dp[i - 1][j << 1 | 1][a2][b2];
							int& d1 = dp[i][j][a1 | a2][b1 | b2];
							d1 = max(d1,x + (a1 | a2) + (b1 | b2) * 2);
							if(a1 | a2) {
								int& d2 = dp[i][j][a1 + a2 - 1][1];
								d2 = max(d2,x + 1 + (i > 1) + (b1 | b2));
							}
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for(int a = 0;a < 2;++a) {
		for(int b = 0;b < 2;++b) {
			ans = max(ans,dp[N][0][a][b] + (a | b));
		}
	}
	cout << ans << endl;
	return 0;
}