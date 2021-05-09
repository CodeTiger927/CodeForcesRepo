using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN 200005

int N,depth[MAXN],parent[MAXN];
vector<int> groups[MAXN];
long long dp[MAXN],arr[MAXN];

int dfs(int x) {
	if(x == 0 || depth[x]) return depth[x];
	depth[x] = 1 + dfs(parent[x]);
	return depth[x];
}

void solve() {
	cin >> N;
	int md = 0;
	for(int i = 1;i < N;++i) {
		cin >> parent[i];
		parent[i]--;
		depth[i] = 0;
		groups[i].clear();
	}
	for(int i = 1;i < N;++i) {
		dfs(i);
		md = max(md,depth[i]);
		groups[depth[i]].push_back(i);
		cin >> arr[i];
	}
	dp[0] = 0;
	for(int i = 1;i <= md;++i) {
		sort(groups[i].begin(),groups[i].end(),[&](int a,int b) {return arr[a] < arr[b];});
		long long max1 = -1e16;
		long long max2 = -1e16;
		for(int j = 0;j < groups[i].size();++j) {
			int cur = groups[i][j];
			// Case 1: not switch
			dp[cur] = dp[parent[cur]] + max(abs(arr[cur] - arr[groups[i][0]]),abs(arr[cur] - arr[groups[i][groups[i].size() - 1]]));	

			// Case 2: Switch, greedily pick dp[parent[i]] + abs
			max1 = max(max1,dp[parent[cur]] + arr[cur]);
			max2 = max(max2,dp[parent[cur]] - arr[cur]);		
		}
		// Case 2: switch
		for(int j = 0;j < groups[i].size();++j) {
			int cur = groups[i][j];
			dp[cur] = max(dp[cur],max(max1 - arr[cur],max2 + arr[cur]));
		}
	}
	long long ans = 0;
	for(int i = 0;i < N;++i) {
		ans = max(ans,dp[i]);
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}