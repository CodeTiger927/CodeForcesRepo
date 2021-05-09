using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 5005
#define MOD 998244353

int N,cntLess[MAXN],lastLess[MAXN];
long long arr[MAXN],dp[MAXN][MAXN],pref[MAXN][MAXN];
// dp[i][j] = increasing sequence is at j, in total i pieces places
// dp[i][j] += dp[i - 1][j] * (cntLess[j] - i + 1)

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		lastLess[i] = -1;
	}
	sort(arr,arr + N);
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < i;++j) {
			if(2 * arr[j] <= arr[i]) {
				cntLess[i]++;
				lastLess[i] = j;
			}
		}
	}
	for(int i = 0;i < N;++i) {
		dp[1][i] = 1;
		pref[1][i + 1] = pref[1][i] + dp[1][i];
	}
	for(int i = 2;i <= N;++i) {
		for(int j = 0;j < N;++j) {
			dp[i][j] = (dp[i - 1][j] * max(0,cntLess[j] - i + 2)) % MOD;
			if(lastLess[j] != -1) {
				dp[i][j] = (dp[i][j] + pref[i - 1][lastLess[j] + 1]) % MOD;
			}
			pref[i][j + 1] = (pref[i][j] + dp[i][j]) % MOD;
		}
	}
	cout << dp[N][N - 1] << endl;

}