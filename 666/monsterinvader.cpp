using namespace std;

#include <iostream>

#define MAXN 1000005

int N;
long long r1,r2,r3,d,arr[MAXN],dp[MAXN][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> r1 >> r2 >> r3 >> d;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
	}
	for(int i = 2;i <= N;++i) {
		dp[i][0] = dp[i][1] = 1e18;
	}
	dp[1][0] = r1 * arr[1] + r3;
	dp[1][1] = min(r2,r1 * (arr[1] + 1));
	for(int i = 1;i < N;++i) {
		dp[i + 1][0] = min(dp[i + 1][0],dp[i][0] + d + r1 * arr[i + 1] + r3);
		dp[i + 1][1] = min(dp[i + 1][1],dp[i][0] + d + min(r2,r1 * (arr[i + 1] + 1)));
		dp[i + 1][0] = min(dp[i + 1][0],dp[i][1] + d + r1 * arr[i + 1] + r3 + 2 * d + r1);
		dp[i + 1][0] = min(dp[i + 1][0],dp[i][1] + d + r1 * (arr[i + 1] + 3) + 2 * d);
		dp[i + 1][0] = min(dp[i + 1][0],dp[i][1] + d + r2 + d + r1 + d + r1);
		dp[i + 1][1] = min(dp[i + 1][1],dp[i][1] + d + r2 + d + r1 + d);
		dp[i + 1][1] = min(dp[i + 1][1],dp[i][1] + d + r1 * (arr[i + 1] + 2) + 2 * d);

		if(i == N - 1) {
			dp[i + 1][0] = min(dp[i + 1][0],dp[i][1] + d + r1 * (arr[i + 1] + 1) + r3 + d);
		}
	}
	cout << dp[N][0] << endl;
	return 0;
}