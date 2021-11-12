using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 100005

int N,P,K;

long long dp[MAXN][128],a[MAXN],b[MAXN][7];
vector<int> v;

int main() {
	cin >> N >> P >> K;
	for(int i = 1;i <= N;++i) {
		cin >> a[i];
		v.push_back(i);
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < P;++j) {
			cin >> b[i][j];
		}
	}
	long long ans = 0;
	sort(v.begin(),v.end(),[&](int i,int j) {return a[i] > a[j];});
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j < (1 << P);++j) dp[i][j] = -1e18;
	}
	dp[0][0] = 0;
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < (1 << P);++j) {
			int c = i - __builtin_popcount(j);
			if(c < 0) continue;
			if(c <= K) {
				dp[i][j] = max(dp[i][j],dp[i - 1][j] + a[v[i - 1]]);
			}else{
				dp[i][j] = max(dp[i][j],dp[i - 1][j]);
			}
			for(int k = 0;k < P;++k) {
				if(~j & (1 << k)) continue;
				dp[i][j] = max(dp[i][j],dp[i - 1][j ^ (1 << k)] + b[v[i - 1]][k]);
			}
			ans = max(ans,dp[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}