using namespace std;

#include <iostream>
#include <algorithm>

#define MOD 998244353
#define MAXN 300005

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int N;
long long arr[MAXN],pref[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	for(int i = 0;i < N;++i) {
		pref[i + 1] = (pref[i] + arr[N - 1 - i]) % MOD;
	}
	long long invN = inv(N);
	for(int i = 1;i <= N;++i) {
		long long ans = 0;
		for(int j = 0;j < N;j += i) {
			ans += (pref[min(N,j + i)] - pref[j] + MOD) % MOD * (j / i) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
		cout << (ans * invN % MOD) << " ";
	}
	return 0;
}