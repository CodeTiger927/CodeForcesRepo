using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define MAXN 20

int N,sum[MAXN],dp[1 << 20][2],a[1 << 20];
map<int,vector<int>> pref[MAXN];
map<int,int> stop[MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		string s;
		cin >> s;
		for(int j = 0;j < s.size();++j) {
			pref[i][sum[i] += s[j] == '(' ? 1 : -1].push_back(j);
			if(!stop[i].count(sum[i])) stop[i][sum[i]] = j;
		}
		for(int j = stop[i].begin() -> first + 1;j <= prev(stop[i].end()) -> first;++j) {
			stop[i][j] = min(stop[i].count(j) ? stop[i][j] : N,stop[i][j - 1]);
		}
	}
	for(int i = 0;i < (1 << N);++i) dp[i][1] = -1e9;
	dp[0][1] = 0;
	int ans = 0;
	for(int i = 1;i < (1 << N);++i) {
		for(int j = 0;j < N;++j) {
			if(~i & (1 << j)) continue;
			int b = pref[j].begin() -> first + a[i ^ (1 << j)] >= 0;
			a[i] = sum[j] + a[i ^ (1 << j)];
			int s = a[i ^ (1 << j)];
			dp[i][b] = max(dp[i][b],dp[i ^ (1 << j)][1] + (b ? (int)(pref[j].count(-s) ? pref[j][-s].size() : 0) : (int)(pref[j].count(-s) ? lower_bound(pref[j][-s].begin(),pref[j][-s].end(),stop[j][-s - 1]) - pref[j][-s].begin() : 0)));
		}
		ans = max(ans,dp[i][0] = max(dp[i][0],dp[i][1]));
	}
	cout << ans << endl;
	return 0;
}