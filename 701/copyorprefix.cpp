using namespace std;

#include <iostream>
#include <map>

#define MAXN 200005
#define MOD 1000000007

int N;
long long arr[MAXN],water_level,sum;
map<long long,long long> dp;

void solve() {
	cin >> N;
	dp.clear();
	water_level = 0;
	sum = dp[0] = 1;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		// when sum = 0
		long long tmp = dp[water_level];
		// dp[b_i] = sum of all dp[j]
		dp[water_level] = sum;
		// move dp[i] to dp[i + b_i]
		water_level -= arr[i];
		// all choices besides overlap when sum = 0
		sum = (2 * sum - tmp + MOD) % MOD;
	}
	cout << sum << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}