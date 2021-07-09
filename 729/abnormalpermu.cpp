using namespace std;

#include <iostream>
#include <vector>
#include <complex>

#define MAXN 505

int N,M,MOD;
long long dp[2 * MAXN * MAXN],f[2 * MAXN * MAXN];

int main() {
	cin >> N >> MOD;
	M = N * N;
	long long res = 0;
	dp[M] = 1;
	for(int i = 1;i <= N;++i) {
		int k = i * i;
		for(int j = M - k + 1;j <= M + k;++j) {
			f[j] = (dp[j] + f[j - 1]) % MOD;
		}
		for(int j = M - k + 1;j <= M + k;++j) {
			dp[j] = (2 * MOD + dp[j - 1] + (f[min(M + k,j + i - 1)] - f[j - 1]) - (f[j - 1] - f[max(M - k,j - i - 1)])) % MOD;
		}
		res = res * i % MOD;
		for(int j = 1;j < i;++j) {
			res += (i - j) * (MOD + f[M + k] - f[M + j]) % MOD;
			if(res >= MOD) res -= MOD;
		}
	}
	cout << res << endl;
	return 0;
}