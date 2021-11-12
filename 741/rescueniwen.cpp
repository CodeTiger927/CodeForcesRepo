using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 5005

int N,lcp[MAXN][MAXN],dp[MAXN];
string s;

void solve() {
	cin >> N >> s;
	lcp[N][N] = 0;
	for(int i = N - 1;i >= 0;--i) {
		for(int j = N - 1;j >= 0;--j) {
			lcp[i][j] = s[i] == s[j] ? lcp[i + 1][j + 1] + 1 : 0;
		}
	}
	int ans = 0;
	for(int i = 0;i < N;++i) {
		dp[i] = N - i;
		for(int j = 0;j < i;++j) {
			int p = lcp[i][j];
			if(p < (N - i) && s[i + p] > s[j + p]) dp[i] = max(dp[i],dp[j] + (N - i) - p);
		}
		ans = max(ans,dp[i]);
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}