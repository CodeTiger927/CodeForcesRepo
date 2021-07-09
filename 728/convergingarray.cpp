using namespace std;

#include <iostream>
#include <cstring>

#define MOD 1000000007
#define MAXN 105

int N,K,Q,a[MAXN],b[MAXN],f[MAXN],dp[MAXN * MAXN];

int main() {
	cin >> N;
	K = N * MAXN;
	for(int i = 1;i <= N;++i) {
		cin >> a[i];
	}
	for(int i = 2;i <= N;++i) {
		cin >> b[i];
		b[i] += b[i - 1];
	}
	int s = 1e9;
	int e = 1e9;
	int pre = 0;
	for(int i = 1;i <= N;++i) {
		pre += a[i];
		b[i] += b[i - 1];
		s = min(s,-b[i] / i - 1);
		e = min(e,(pre - b[i]) / i + 1);
	}
	for(int i = s;i <= e;++i) {
		memset(dp,0,sizeof(dp));
		dp[0] = 1;
		for(int j = 1;j <= N;++j) {
			for(int k = 1;k <= K;++k) {
				dp[k] += dp[k - 1];
				if(dp[k] >= MOD) dp[k] -= MOD;
			}
			for(int k = K;~k;--k) {
				if(k < i * j + b[j]) {
					dp[k] += MOD - dp[k];
				}else if(k > a[j]) {
					dp[k] += MOD - dp[k - a[j] - 1];
				}
				dp[k] %= MOD;
			}
		}
		for(int j = 0;j <= K;++j) {
			f[i - s] += dp[j];
			if(f[i - s] >= MOD) f[i - s] -= MOD;
		}
	}
	cin >> Q;
	while(Q--) {
		int x;
		cin >> x;
		x = max(s,min(x,e));
		cout << f[x - s] << endl;
	}
	return 0;
}