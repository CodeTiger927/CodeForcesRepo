using namespace std;

#include <iostream>

#define MAXN 405
#define MOD 1000000007

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int N,K;
long long fact[MAXN],invfact[MAXN],revfact[MAXN],dp[MAXN][MAXN];

long long ncr(int a,int b) {
	return (fact[a] * invfact[a - b] % MOD) * invfact[b] % MOD;
}

long long big_ncr(int a) {
	return revfact[a] * invfact[a] % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	fact[0] = revfact[0] = invfact[0] = 1;
	cin >> N >> K;
	for(int i = 1;i <= 2 * K;++i) {
		fact[i] = (fact[i - 1] * i) % MOD;
		invfact[i] = inv(fact[i]);
	}
	for(int i = 0;i < min(2 * K,N);++i) {
		revfact[i + 1] = (revfact[i] * (N - i)) % MOD;
	}
	for(int i = 1;i <= 2 * K;++i) {
		dp[i][0] = 1;
		for(int j = 1;j <= 2 * K;++j) {
			dp[i][j] = (dp[i - 1][j] + (i - 1) * dp[i - 1][j - 1]) % MOD;
		}
	}
	int ans[2] = {1,0};
	for(int i = 1;i <= K;++i) {
		// cout << i << endl;
		for(int j = 1;j <= min(N,2 * i);++j) {
			long long cur = 0;
			for(int k = 0;k <= j;++k) {
				cur += ((k % 2 ? (MOD - 1) : 1) * ncr(j,k) % MOD) * dp[j - k][i] % MOD;
				if(cur >= MOD) cur -= MOD;
			}
			ans[i % 2] += big_ncr(j) * cur % MOD;
			if(ans[i % 2] >= MOD) ans[i % 2] -= MOD;
		}
		cout << ans[i % 2] << " ";
	}
	cout << endl;
	return 0;
}