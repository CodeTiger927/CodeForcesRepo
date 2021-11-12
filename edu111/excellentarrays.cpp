using namespace std;

#include <iostream>

#define MOD 1000000007
#define MAXN 200005

int N,L,R;
long long fact[MAXN],invf[MAXN];

long long exp(long long a,long long b) {
	if(b == 0) return 1;
	if(b == 1) return a;
	long long res = exp(a,b >> 1);
	if(b & 1) {
		return a * (res * res % MOD) % MOD;
	}
	return res * res % MOD;
}

long long nCr(long long a,long long b) {
	if(b < 0 || b > a) return 0;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

void solve() {
	cin >> N >> L >> R;
	int half = N >> 1;
	int st = min(1 - L,R - N);
	long long ans = st * nCr(N,half) * (1 + (N & 1)) % MOD;
	for(int i = st + 1;;++i) {
		int l = max(1,L + i);
		int r = min(N,R - i);
		if(r + 1 - l < 0) break;
		ans += nCr(r + 1 - l,half - l + 1);
		if(ans >= MOD) ans -= MOD;
		if(N & 1) {
			ans += nCr(r + 1 - l,half - l + 2);
			if(ans >= MOD) ans -= MOD;
		}
	}
	cout << ans << endl;
	return;
}


int main() {
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = fact[i - 1] * i % MOD;
		invf[i] = exp(fact[i],MOD - 2);
	}
	int T;
	cin >> T;
	while(T--) solve();
}