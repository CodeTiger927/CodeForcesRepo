using namespace std;

#include <iostream>

#define MAXN 505

int N,K;
long long a,b;
bool dp[MAXN][MAXN];

int main() {
	cin >> N >> K;
	dp[0][0] = true;
	for(int i = 0;i < N;++i) {
		long long x,y;
		cin >> x >> y;
		a += x;b += y;
		for(int j = 0;j < K;++j) {
			if(!dp[i][j]) continue;
			dp[i + 1][j] = true;
			for(int k = max(0ll,K - y);k <= min((int)x,K);++k) {
				dp[i + 1][(j + k) % K] = true;
			}
		}
	}
	long long ans = 0;
	for(int i = K - (b % K);i <= (a % K);++i) {
		ans |= dp[N][i];
	}
	ans += a / K + b / K;
	cout << ans << endl;
	return 0;	
}