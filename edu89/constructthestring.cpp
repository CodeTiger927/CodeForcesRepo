using namespace std;

#include <iostream>

#define MAXN 10005

string s,t;
int N,M,dp[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s >> t;
	N = s.size();
	M = t.size();
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j <= M;++j) {
			dp[i][j] = MAXN;
		}
	}
	dp[0][0] = 0;
	for(int i = 0;i < N;++i) {
		int cur = 0;
		int nxt = -1;
		for(int j = i;j < N;++j) {
			cur += (s[j] == '.' ? -1 : 1);
			if(cur < 0) break;
			if(cur == 0) {
				nxt = j + 1;
				break;
			}
		}
		for(int j = 0;j <= M;++j) {
			dp[i + 1][j] = min(dp[i + 1][j],dp[i][j] + 1);
			if(j && s[i] == '.') {
				dp[i + 1][j - 1] = min(dp[i + 1][j - 1],dp[i][j]);
			}
			if(s[i] == t[j]) {
				dp[i + 1][j + 1] = min(dp[i + 1][j + 1],dp[i][j]);
			}
			if(~nxt) dp[nxt][j] = min(dp[nxt][j],dp[i][j]);
		}
	}
	cout << dp[N][M] << endl;
	return 0;
}