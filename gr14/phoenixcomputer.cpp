using namespace std;

#include <iostream>

#define MAXN 405

int N;
long long M,dp[2][MAXN][MAXN],pref[2][MAXN][MAXN],sum[MAXN][MAXN];

int main() {
	cin >> N >> M;
	if(N == 1) {
		cout << 1 << endl;
		return 0;
	}
	dp[1][0][1] = dp[1][1][0] = 1;
	dp[0][0][0] = 1;
	pref[1][1][0] = pref[1][0][0] = pref[1][0][1] = 1;
	pref[0][0][0] = 1;
	sum[1][0] = sum[1][1] = 1;
	sum[0][0] = 1;
	for(int i = 2;i < N;++i) {
		for(int j = 0;j <= i;++j) {
			for(int k = 0;k <= i;++k) {
				dp[i & 1][j][k] = 0;
				if(j < k) {
					dp[i & 1][j][k] = pref[(i + 1) & 1][0][j] - dp[(i + 1) & 1][j + 1][j];
				}else if(j > k) {
					dp[i & 1][j][k] = pref[(i + 1) & 1][j - 1][j - 1];
					if(j > 1 && j > k + 1) {
						dp[i & 1][j][k] += sum[i - 2][j - 2];
						if(dp[i & 1][j][k] >= M) dp[i & 1][j][k] -= M;
					}
				}
			}
			for(int k = 0;k < j - 1;++k) {
				dp[i & 1][j][j - 1] += sum[i - 2][k];
				if(dp[i & 1][j][j - 1] >= M) dp[i & 1][j][j - 1] -= M;
			}
		}
		for(int k = 0;k <= i;++k) {
			for(int j = i;j >= 0;--j) {
				sum[i][k] = (sum[i][k] + dp[i & 1][j][k]) % M;
				pref[i & 1][j][k] = (pref[i & 1][j + 1][k] + dp[i & 1][j][k]) % M;
			}
		}
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			if(dp[(N - 1) & 1][i][j] > 0) {
				cout << i << " " << j << " " << dp[(N - 1) & 1][i][j] << endl;
			}
			ans += dp[(N - 1) & 1][i][j];
			if(ans >= M) ans -= M;
		}
	}
	cout << ans << endl;
	return 0;
}