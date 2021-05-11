using namespace std;

#include <iostream>
#include <algorithm>
#include <assert.h>

#define MOD 998244353
#define MAXN 200005

long long N,M;
long long arr[MAXN],pref[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	for(int i = 0;i < N;++i) {
		pref[i + 1] = (pref[i] + arr[i]) % MOD;
	}
	for(int i = 0;i < M;++i) {
		long long a,b;
		cin >> a >> b;
		long long ind = lower_bound(arr,arr + N,b) - arr;
		long long small = pref[ind];
		long long big = pref[N] - pref[ind];
		if(N - ind - a < 0 || a == N) {
			cout << 0 << endl;
			continue;
		}
		long long ans = (big * (1ll * (N - ind - a) * inv(N - ind) % MOD) % MOD) + (small * (1ll * (N - ind - a + 1) * inv(N - ind + 1) % MOD) % MOD);
		if(ans < 0) ans += MOD;
		if(ans >= MOD) ans -= MOD;
		cout << ans << endl;		
	}
	return 0;
}