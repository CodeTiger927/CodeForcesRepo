using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 200005

int N,K,pref[MAXN][17],nxt[MAXN][17],dp[1 << 17];
string str;

bool check(int n) {
	if(!n) return true;
	for(int i = 0;i < K;++i) {
		nxt[N][i] = N;
	}
	for(int i = N - 1;i >= 0;--i) {
		for(int j = 0;j < K;++j) {
			nxt[i][j] = nxt[i + 1][j];
			if(i + n <= N && pref[i + n][j] - pref[i][j] == n) {
				nxt[i][j] = i + n - 1;
			}
		}
	}
	dp[0] = -1;
	for(int i = 1;i < (1 << K);++i) {
		dp[i] = N;
		for(int j = 0;j < K;++j) {
			if(!(i & (1 << j))) continue;
			if(dp[i ^ (1 << j)] != N) dp[i] = min(dp[i],nxt[dp[i ^ (1 << j)] + 1][j]);
		}
	}
	return dp[(1 << K) - 1] < N;
}

int main() {
	cin >> N >> K >> str;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < K;++j) {
			pref[i + 1][j] = pref[i][j];
			if(str[i] - 'a' == j || str[i] == '?') {
				pref[i + 1][j]++;
			}
		}
	}
	int l = 0;
	int r = N;
	while(l < r) {
		int m = (l + r + 1) >> 1;
		if(check(m)) {
			l = m;
		}else{
			r = m - 1;
		}
	}
	cout << l << endl;
	return 0;
}
