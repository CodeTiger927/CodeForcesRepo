using namespace std;

#include <iostream>

long long dp[75][75][75],arr[75][75];
long long dp2[75][75];

long long N,M,K;

int main() {
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j <= M / 2;++j) {
			for(int k = 0;k < K;++k) {
				dp[i][j][k] = -999999999999;
			}
		}
	}
	for(int i = 0;i < N;++i) {
		dp[i][0][0] = 0;
		for(int l = 0;l < M;++l) {
			for(int j = M / 2;j >= 1;--j) {
				for(int k = 0;k < K;++k) {
					dp[i][j][k] = max(dp[i][j][k],dp[i][j - 1][k]);
					// cout << i << " " << j << " " << k << endl;
					dp[i][j][k] = max(dp[i][j][k],dp[i][j - 1][(k + K - (arr[i][l] % K)) % K] + arr[i][l]);
				}
			}
		}
	}
	for(int i = 0;i < K;++i) {
		dp2[0][i] = dp[0][M / 2][i];
	}
	for(int i = 1;i < N;++i) {
		for(int j = 0;j < K;++j) {
			dp2[i][j] = -999999999999;
			for(int k = 0;k < K;++k) {
				dp2[i][j] = max(dp2[i][j],dp[i][M / 2][k] + dp2[i - 1][(j - k + K) % K]);
				// if(dp2[i][j] == 18) {
				// 	cout << i << " " << j << " " << k << endl;
				// }
			}
		}
	}
	cout << dp2[N - 1][0] << endl;
}