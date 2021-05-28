using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005
#define MOD 998244353

int N,K,arr[MAXN],pos[MAXN];
long long fact[MAXN],invf[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long nCr(long long a,long long b) {
	if(b > a) return 0;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

long long solve() {
	int cnt = 0;
	for(int i = 0;i < N;++i) {
		if(arr[i] != N - 1 && )

	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = (i * fact[i - 1]) % MOD;
		invf[i] = (inv(i) * invf[i - 1]) % MOD;
	}
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		pos[arr[i]] = i;
	}
	cout << solve() << endl;
	return 0;
}