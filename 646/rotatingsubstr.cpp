using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 2005

int N,suf[MAXN][26],suf2[MAXN][26],dp[MAXN][MAXN];
string s,t;

int solve(int i,int j) {
	if(j == 0) return 0;
	int& ans = dp[i][j];
	if(ans != -1) return ans;
	ans = 1e9;
	if(i > 0) {
		ans = 1 + solve(i - 1,j);
		if(s[i - 1] == t[j - 1]) ans = min(ans,solve(i - 1,j - 1));
	}
	int c = t[j - 1] - 'a';
	if(suf[i + 1][c] > suf2[j + 1][c]) ans = min(ans,solve(i,j - 1));
	return ans;
}

void solve() {
	cin >> N >> s >> t;
	for(int i = 0;i <= N + 1;++i) {
		for(int j = 0;j <= N + 1;++j) dp[i][j] = -1;
		for(int j = 0;j < 26;++j) suf[i][j] = suf2[i][j] = 0;
	}
	for(int i = N;i >= 1;--i) {
		for(int j = 0;j < 26;++j) suf[i][j] = suf[i + 1][j];
		for(int j = 0;j < 26;++j) suf2[i][j] = suf2[i + 1][j];

		suf[i][s[i - 1] - 'a']++;
		suf2[i][t[i - 1] - 'a']++;
	}
	int ans = solve(N,N);
	cout << (ans >= 1e9 ? -1 : ans) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}