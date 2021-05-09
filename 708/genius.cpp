using namespace std;

#include <iostream>

#define MAXN 5005

long long dp[MAXN],arr[MAXN],tag[MAXN],N;

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> tag[i];
		dp[i] = 0;
	}
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < N;++i) {
		for(int j = i - 1;j >= 0;--j) {
			if(tag[i] == tag[j]) continue;
			long long tmp = dp[i];
			dp[i] = max(dp[i],dp[j] + abs(arr[i] - arr[j]));
			dp[j] = max(dp[j],tmp + abs(arr[i] - arr[j]));
		}
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		ans = max(ans,dp[i]);
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}