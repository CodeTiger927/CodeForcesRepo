using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 6005
#define MAXA 200005

int N,dp[MAXN][MAXN],L[MAXN],R[MAXN],rev[MAXA];
vector<int> segs[MAXN],v;
set<int> s;

int solve(int l,int r) {
	if(l > r) return 0;
	if(dp[l][r] != -1) return dp[l][r];
	int& res = dp[l][r];
	res = max(0,solve(l,r - 1));
	bool exist = false;
	for(int x : segs[r]) {
		if(x == l) exist = true;
		if(x <= l) continue;
		res = max(res,solve(l,x - 1) + solve(x,r));
	}
	res += exist;
	return res;
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> L[i] >> R[i];
		s.insert(L[i]);
		s.insert(R[i]);
	}
	int cnt = 0;
	for(int x : s) {
		rev[x] = cnt++;
	}
	for(int i = 0;i < cnt;++i) {
		segs[i].clear();
	}
	for(int i = 0;i < N;++i) {
		segs[rev[R[i]]].push_back(rev[L[i]]);
	}
	for(int i = 0;i < 2 * N;++i) {
		for(int j = i;j < 2 * N;++j) {
			dp[i][j] = -1;
		}
	}
	// cout << solve()
	cout << solve(0,2 * N - 1) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}