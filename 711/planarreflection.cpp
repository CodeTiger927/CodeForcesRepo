using namespace std;

#include <iostream>

#define MAXN 1005
#define MOD 1000000007

int N,K;
long long dp[MAXN][MAXN];

long long calc(int a,int b) {
	if(a > N) return 1;
	if(dp[a][b] != -1) return dp[a][b];
	if(b == 1) return 1;
	dp[a][b] = (calc(a + 1,b) + calc(N - a + 2,b - 1)) % MOD;
	return dp[a][b];
}

void solve() {
	cin >> N >> K;
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j <= K;++j) {
			dp[i][j] = -1;
		}
	}
	cout << calc(1,K) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}