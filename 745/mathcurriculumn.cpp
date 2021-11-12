#pragma GCC optimize("Ofast")
#pragma GCC optimization ("unroll-loops")
using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 105

int N,M,K,MOD;
long long dp[MAXN][MAXN][MAXN],f[MAXN],C[MAXN][MAXN];

long long solve(int n,int m,int k) {
	if(n < m) return !k * f[n];
	if(!~-m) return (!~-k) * f[n];
	if(m < 0 || n < m || n - m + 1 < k) return 0;
	long long &cur = dp[n][m][k];
	if(~cur) return cur;
	cur = 0;
	for(int i = 0;i < n;++i) {
		for(int j = 0;j <= k;++j) {
			(cur += C[n - 1][i] * solve(i,m - 1,j) % MOD * solve(n - i - 1,m - 1,k - j)) %= MOD;		}
	}
	return cur;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K >> MOD;
	f[0] = C[0][0] = 1;
	for(int i = 1;i <= N;++i) {
		f[i] = i * f[i - 1] % MOD;
		C[i][0] = 1;
		for(int j = 1;j <= N;++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	memset(dp,-1,sizeof(dp));
	cout << solve(N,M,K) << endl;
	return 0;
}