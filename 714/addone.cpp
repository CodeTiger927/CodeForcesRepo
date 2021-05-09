using namespace std;

#include <iostream>
#include <cstring>

#define MAXM 200005
#define MOD 1000000007

string str;
long long M,dp[MAXM][10];

void solve() {
	cin >> str >> M;
	long long ans = 0;
	for(int i = 0;i < str.size();++i) {
		ans += dp[M][str[i] - '0'];
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	return;
}

void init() {
	for(int i = 0;i < 10;++i) {
		dp[0][i] = 1;
	}
	for(int i = 1;i < MAXM;++i) {
		for(int j = 0;j < 10;++j) {
			if(j == 9) {
				dp[i][j] = (dp[i - 1][0] + dp[i - 1][1]);
				if(dp[i][j] >= MOD) dp[i][j] -= MOD;
			}else{
				dp[i][j] = dp[i - 1][j + 1];
			}
		}
	}
	return;
}

int main() {
	init();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) solve();
}