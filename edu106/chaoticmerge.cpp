using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 1005
#define MOD 998244353

int N,M;
string s,t;
long long dp[MAXN][MAXN][2];

int main() {
	cin >> s >> t;
	N = s.size();
	M = t.size();
	long long ans = 0;
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j <= M;++j) {
			if(i > 0) {
				dp[i][j][0]++;
			}
			if(j > 0) {
				dp[i][j][1]++;
			}
			if(i > 1 && s[i - 1] != s[i - 2]) {
				dp[i][j][0] += dp[i - 1][j][0];
			}
			if(j > 1 && t[j - 1] != t[j - 2]) {
				dp[i][j][1] += dp[i][j - 1][1];
			}
			if(i > 0 && j > 0 && s[i - 1] != t[j - 1]) {
				dp[i][j][0] += dp[i - 1][j][1];
				dp[i][j][1] += dp[i][j - 1][0];
			}
			dp[i][j][0] %= MOD;
			dp[i][j][1] %= MOD;
			ans += (dp[i][j][0] + dp[i][j][1]) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
	}
	for(int i = 0;i < N;++i) {
		int j = i;
		while(j + 1 < N && s[j] != s[j + 1]) ++j;
		long long len = j - i + 1;
		long long tmp = ((1ll * len * (len + 1) / 2) % MOD) * (M + 1) % MOD;
		ans = (ans + MOD - tmp) % MOD;
		i = j;
	}
	for(int i = 0;i < M;++i) {
		int j = i;
		while(j + 1 < M && t[j] != t[j + 1]) ++j;
		long long len = j - i + 1;
		long long tmp = ((1ll * len * (len + 1) / 2) % MOD) * (N + 1) % MOD;
		ans = (ans + MOD - tmp) % MOD;
		i = j;
	}
	cout << ans << endl;
	return 0;
}