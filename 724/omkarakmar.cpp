using namespace std;

#include <iostream>

#define MAXN 1000005
#define MOD 1000000007

int N;
long long fact[MAXN],invf[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long nCr(long long a,long long b) {
	if(a < 0 || b < 0 || a < b) return 0;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

int main() {
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		invf[i] = (inv(i) * invf[i - 1]) % MOD;
	}
	cin >> N;
	long long ans = 0;
	for(int i = 0;i <= N;i += 2) {
		ans += (nCr(i,N - i) + nCr(i - 1,N - i - 1)) * fact[i] % MOD;
		if(ans >= MOD) ans -= MOD;
	}
	ans = (2ll * ans) % MOD;
	cout << ans << endl;
	return 0;
}