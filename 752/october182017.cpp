using namespace std;

#include <iostream>

#define MAXN 10000005
#define MOD 998244353

int T,pw[MAXN],N,K,X,c[MAXN],d[MAXN];

long long exp(long long a,long long b) {
	if(b == 0) return 1;
	if(b == 1) return a;
	long long res = exp(a,b >> 1);
	if(b & 1) {
		return a * (res * res % MOD) % MOD;
	}
	return res * res % MOD;
}

void solve() {
	cin >> N >> K >> X;
	if(!X) {
		if(K == 0 || N > K) {
			cout << 0 << endl;
			return;
		}
		long long ans = 1;
		for(int i = 0;i < N;++i) {
			ans = 1ll * ans * ((long long)MOD + pw[K] - pw[i]) % MOD;
		}
		cout << ans << endl;
		return;
	}
	d[K] = 1;
	for(int i = K - 1;i >= 0;--i) {
		c[i] = 1ll * pw[i] * d[i + 1] % MOD;
		d[i] = 1ll * (pw[i] - 1) * d[i + 1] % MOD;
	}
	long long ans = 0;
	long long pwn = exp(2,N);
	long long cur = 1;
	for(int i = 0;i < K;++i) {
		ans += 1ll * ((K - i - 1) & 1 ? MOD - 1 : 1) * (1ll * c[i] * cur % MOD) % MOD;
		if(ans >= MOD) ans -= MOD;
		cur = cur * pwn % MOD;
	}
	cout << ans << endl;
	return;
}

int main() {
	pw[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		pw[i] = pw[i - 1] << 1;
		if(pw[i] >= MOD) pw[i] -= MOD;
	}
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}