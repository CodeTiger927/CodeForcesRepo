using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 500005

int N,M;
pair<vector<int>,int> a[MAXN];
vector<int> pre[MAXN],pre2[MAXN],suf[MAXN],suf2[MAXN],v;

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		a[i].second = i;
		a[i].first.resize(M);
		for(int j = 0;j < M;++j) {
			cin >> a[i].first[j];
		}
	}
	sort(a,a + N,[&](pair<vector<int>,int>& x,pair<vector<int>,int>& y) {return x.first[0] > y.first[0];});
	for(int i = 0;i < N;++i) {
		pre[i].resize(M);
		for(int j = 0;j < M;++j) {
			pre[i][j] = min({a[i].first[j],i > 0 ? pre[i - 1][j] : (int)1e9,j > 0 ? pre[i][j - 1] : (int)1e9});
		}
	}
	for(int i = 0;i < N;++i) {
		pre2[i].resize(M);
		for(int j = M - 1;j >= 0;--j) {
			pre2[i][j] = max({a[i].first[j],i > 0 ? pre2[i - 1][j] : 0,j < M - 1 ? pre2[i][j + 1] : 0});
		}
	}
	for(int i = N - 1;i >= 0;--i) {
		suf[i].resize(M);
		for(int j = 0;j < M;++j) {
			suf[i][j] = max({a[i].first[j],i < N - 1 ? suf[i + 1][j] : 0,j > 0 ? suf[i][j - 1] : 0});
		}
	}
	for(int i = N - 1;i >= 0;--i) {
		suf2[i].resize(M);
		for(int j = M - 1;j >= 0;--j) {
			suf2[i][j] = min({a[i].first[j],i < N - 1 ? suf2[i + 1][j] : (int)1e9,j < M - 1 ? suf2[i][j + 1] : (int)1e9});
		}
	}
	for(int i = 0;i < N - 1;++i) {
		for(int j = 0;j < M - 1;++j) {
			if(pre[i][j] > suf[i + 1][j] && pre2[i][j + 1] < suf2[i + 1][j + 1]) {
				string ans = string(N,'B');
				for(int k = 0;k <= i;++k) {
					ans[a[k].second] = 'R';
				}
				cout << "YES" << endl << ans << " " << (j + 1) << endl;
				return;
			}
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}