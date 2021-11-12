using namespace std;

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

#define MAXN 200005

int N,M;
long long dp1,dp2,suf[MAXN],pref[MAXN],a[MAXN];
vector<pair<long long,long long>> v[MAXN];

void solve() {
	cin >> N >> M;
	v[N].clear();
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		v[i].clear();
	}
	sort(a,a + N);
	for(int i = 0;i < M;++i) {
		long long x,y;
		cin >> x >> y;
		int j = lower_bound(a,a + N,x) - a;
		if(j == N || (y < a[j])) {
			// cout << i << " " << j << endl;
			v[j].push_back({x,y});
		}
	}
	long long dist = 0;
	for(auto p : v[0]) {
		dist = max(dist,a[0] - p.second);
	}
	dp1 = dist;
	dp2 = dist * 2;
	for(int i = 1;i < N;++i) {
		sort(v[i].begin(),v[i].end());
		int n = v[i].size();
		suf[n] = 0;
		for(int j = n - 1;j >= 0;--j) {
			suf[j] = max(suf[j + 1],a[i] - v[i][j].second);
		}
		for(int j = 0;j < n;++j) {
			pref[j + 1] = max(pref[j],v[i][j].first - a[i - 1]);
		}
		long long ndp1 = 4e18;
		long long ndp2 = 4e18;
		for(int j = 0;j <= n;++j) {
			ndp1 = min(ndp1,dp2 + pref[j] * 1 + suf[j] * 1);
			ndp1 = min(ndp1,dp1 + pref[j] * 2 + suf[j] * 1);
			ndp2 = min(ndp2,dp2 + pref[j] * 1 + suf[j] * 2);
			ndp2 = min(ndp2,dp1 + pref[j] * 2 + suf[j] * 2);
		}
		dp1 = ndp1;
		dp2 = ndp2;
	}
	dist = 0;
	for(auto p : v[N]) {
		dist = max(dist,p.first - a[N - 1]);
	}
	cout << min(dp1 + dist * 2,dp2 + dist) << "\n";
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}