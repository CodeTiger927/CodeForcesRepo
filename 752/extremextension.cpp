using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005
#define MOD 998244353

int N,a[MAXN];
long long dp[2][MAXN];
vector<int> v[2];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
	}
	long long ans = 0;
	for(int i = N - 1;i >= 0;--i) {
		int k = i & 1;
		int last = a[i];
		dp[k][a[i]] = 1;
		v[k].push_back(a[i]);
		for(int j : v[k ^ 1]) {
			long long s = (a[i] + j - 1) / j;
			long long x = a[i] / s;

			// if(i == N - 1) cout << j << "    " << x << " " << dp[k][x] << " " << dp[k ^ 1][j] << endl;
			dp[k][x] += dp[k ^ 1][j];
			if(dp[k][x] >= MOD) dp[k][x] -= MOD;
			// cout << i << " " << dp[k ^ 1][j] << " " << (s - 1) << endl;
			ans += 1ll * (i + 1) * dp[k ^ 1][j] * (s - 1) % MOD;
			if(ans >= MOD) ans -= MOD;
			dp[k ^ 1][j] = 0;
			if(last != x) {
				v[k].push_back(last = x);
			}
		}
		v[k ^ 1].clear();
	}
	for(int i : v[0]) {
		dp[0][i] = 0;
	}
	v[0].clear();
	cout << ans << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}