using namespace std;

#include <iostream>

#define MAXN 2005

int N;
long long K,dp[MAXN],l[MAXN],r[MAXN],a[MAXN];

int main() {
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> l[i] >> r[i] >> a[i];
		dp[i] = 1e18;
	}
	dp[0] = 0;
	long long ans = 1e18;
	for(int i = 0;i < N;++i) {
		long long total = dp[i];
		long long rem = K;
		for(int j = i;j < N;++j) {
			long long cnt = (max(0ll,a[j] - rem) + K - 1) / K;
			if(cnt > (r[j] - l[j])) break;
			long long nrem = rem + K * cnt - a[j];
			total += a[j];
			if(j == N - 1) {
				ans = min(ans,total);
			}else{
				if(l[j] + cnt < l[j + 1]) {
					dp[j + 1] = min(dp[j + 1],total + nrem);
				}
			}
			rem = nrem;
		}
	}
	cout << (ans == 1e18 ? -1 : ans) << endl;
}