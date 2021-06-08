using namespace std;

#include <iostream>

#define MAXN 100005
#define MOD 1000000007

int N,K;
long long fact[MAXN],invf[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long nCr(long long a,long long b) {
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

long long inCr(long long a,long long b) {
	return (invf[a] * fact[b] % MOD) * fact[a - b] % MOD;
}

void solve() {
	cin >> N >> K;
	int ans = 1;
	for(int i = 1;i <= N && i + (i - 1) * (K - 1) <= N;++i) {
		ans += nCr(N - (i - 1) * (K - 1),i) * inCr(N,i) % MOD;
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return;
}

int main() {
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		invf[i] = (inv(i) * invf[i - 1]) % MOD;
	}

	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}