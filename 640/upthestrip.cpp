using namespace std;

#include <iostream>

#define MAXN 4000005

int N;
long long dp[MAXN],pref[MAXN],MOD;

long long get(int a,int b) {
	long long res = pref[max(0,a)] - pref[min(b,N) + 1];
	if(res < 0) res += MOD;
	return res;
}

int main() {
	cin >> N >> MOD;
	pref[N] = dp[N] = 1;
	for(int i = N - 1;i >= 1;--i) {
		dp[i] = get(i + 1,N);
		for(int j = 2;1ll * i * j <= N;++j) {
			dp[i] += get(j * i,j * (i + 1) - 1);
			if(dp[i] >= MOD) dp[i] -= MOD;
		}
		pref[i] = pref[i + 1] + dp[i];
		if(pref[i] >= MOD) pref[i] -= MOD;
	}
	cout << dp[1] << endl;
	return 0;
}