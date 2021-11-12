using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,K,M,seg[8];
long long dp[MAXN][256];
vector<pair<int,int>> v;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for(int i = 1;i <= N;++i) {
		int l,r;
		cin >> l >> r;
		v.push_back({l,i});
		v.push_back({r + 1,-i});
	}
	sort(v.begin(),v.end());
	int cur = 0;
	for(int i = 1;i <= 2 * N;++i) {
		int x = 0;
		if(v[i - 1].second > 0) {
			while(cur & (1 << x)) x++;
			seg[x] = v[i - 1].second;
		}else{
			while(seg[x] != -v[i - 1].second) x++;
		}
		cur ^= (1 << x);
		for(int j = 0;j < (1 << K);++j) {
			if((j | cur) != cur) continue;
			if(cur & (1 << x)) {
				dp[i][j] = dp[i - 1][j & ~(1 << x)];
			}else{
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j ^ (1 << x)]);
			}
			if(__builtin_parity(j) && i + 1 <= 2 * N) {
				dp[i][j] += v[i].first - v[i - 1].first;
			}
		}
	}
	cout << dp[2 * N][0] << endl;
	return 0;
}