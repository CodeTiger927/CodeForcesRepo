using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 505

int N,dp[MAXN][2];
string s,t;

void solve() {
	cin >> s >> t;
	N = s.length();
	memset(dp,0,sizeof(dp));
	for(int i = 0;i < N;++i) {
		int cnt = 0;
		for(int j = i;j < N && cnt < t.length();++j) {
			if(s[j] == t[cnt]) {
				cnt++;
				dp[j][0] = max(dp[j][0],cnt);
			}else{
				break;
			}
		}
		cnt = 0;
		for(int j = i;j < N && cnt < t.length();++j) {
			if(s[j] == t[t.length() - 1 - cnt]) {
				cnt++;
				dp[j][1] = max(dp[j][1],cnt);
			}else{
				break;
			}
		}
	}
	for(int j = 0;j < N;++j) {
		if(dp[j][0] + dp[j][1] > t.length()) {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}