using namespace std;

#include <iostream>

#define MAXN 3005
#define INF 1e8

int N,arr[MAXN],dp[MAXN][MAXN];

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
	}
	for(int i = 2;i <= N;++i) {
		for(int j = i;j <= N;++j) {
			dp[i][j] = INF;
		}
		int cnt = 0;
		for(int j = i - 1;j >= 1;--j) {
			if(j + arr[j] >= i) {
				dp[i][j + arr[j]] = min(dp[i][j + arr[j]],dp[j][i - 1] + cnt++);
			}
		}
		for(int j = i + 1;j <= N;++j) {
			dp[i][j] = min(dp[i][j],dp[i][j - 1]);
		}
	}
	cout << dp[N][N] << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}