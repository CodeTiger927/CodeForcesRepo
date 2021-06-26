using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 105
#define MOD 1000000007

int N,Q,b[MAXN],c[MAXN],q[MAXN];
// dp[i][j][k] = last i, last number is j, sum is k
long long dp[2][MAXN][2 * MAXN * MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) cin >> c[i];
	for(int i = 0;i < N - 1;++i) cin >> b[i];
	for(int i = 0;i <= c[N - 1];++i) {
		dp[(N - 1) & 1][i][0] = 1;
	}
	for(int i = N - 1;i > 0;--i) {
		memset(dp[(i - 1) & 1],0,sizeof(dp[(i - 1) & 1]));
		for(int j = 0;j <= c[i];++j) {
			for(int k = 0;k <= (N - i - 1) * 200;++k) {
				if(!dp[i & 1][j][k]) continue;
				for(int x = 0;x <= c[i - 1];++x) {
					int t = b[i - 1] - (j - x);
					int nk = 0;
					if(t >= 0) {
						nk = t + max(0,k + t);
					}else{
						nk = max(0,k + 2 * t);
					}
					dp[(i - 1) & 1][x][nk] += dp[i & 1][j][k];
					if(dp[(i - 1) & 1][x][nk] >= MOD) dp[(i - 1) & 1][x][nk] -= MOD;
				}
			}
		}
	}
	cin >> Q;
	for(int i = 0;i < Q;++i) cin >> q[i];
	long long ans = 0;
	for(int i = 0;i <= c[0];++i) {
		for(int j = 0;j <= 100 * 200;++j) {
			long long cur = 2 * i - j;
			if(dp[0][i][j]) cout << i << " " << j << " " << cur << " " << dp[0][i][j] << endl;
			if(cur >= 2 * q[0]) {
				ans += dp[0][i][j];
			}
		}
	}
	cout << ans << endl;
	return 0;
}