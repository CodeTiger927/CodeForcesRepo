using namespace std;

#include <iostream>

#define MAXN 14
#define MOD 1000000007

int N;
long long arr[MAXN],dp[1 << MAXN],aux[MAXN][1 << MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long G(int x,int y) {
	long long res = 1;
	for(int i = 0;i < N;++i) {
		if(!(x & (1 << i))) continue;
		res = res * aux[i][y] % MOD;
	}
	return res;
}

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < (1 << N);++j) {
			aux[i][j] = 1;
			for(int k = 0;k < N;++k) {
				if(j & (1 << k)) {
					aux[i][j] = aux[i][j] * (arr[i] * inv(arr[i] + arr[k]) % MOD) % MOD;
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 0;i < (1 << N);++i) {
		dp[i] = 1;
		for(int j = i & (i - 1);j;j = (j - 1) & i) {
			dp[i] = dp[i] + MOD - (dp[j] * G(j,i ^ j) % MOD);
			if(dp[i] >= MOD) dp[i] -= MOD;
		}
		ans += (__builtin_popcount(i) * dp[i] % MOD) * G(i,(1 << N) - 1 - i) % MOD;
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return 0;
}