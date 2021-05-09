using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005
#define INF (1e18 + 5)

long long dp[MAXN];
vector<int> ans;

void solve(int bias,int N,long long K) {
	if(N == 0) return;
	long long cur = 0;
	for(int i = 0;i < N;++i) {
		if(K > cur && K <= cur + dp[N - i - 1]) {
			for(int j = i + 1;j >= 1;--j) {
				ans.push_back(j + bias);
			}
			solve(bias + i + 1,N - i - 1,K - cur);
			return;
		}
		cur = min(cur + dp[N - i - 1],(long long)INF);
	}
	return;
}

void solve() {
	int n;
	long long k;
	cin >> n >> k;
	ans.clear();
	solve(0,n,k);
	if(k > dp[n]) {
		cout << -1 << endl;
		return;
	}
	for(int x : ans) {
		cout << x << " ";
	}
	cout << endl;
	return;
}

int main() {
	dp[0] = dp[1] = 1;
	for(int i = 2;i < MAXN;++i) {
		dp[i] = min(2ll * dp[i - 1],(long long)INF);
	}
	int T;
	cin >> T;
	while(T--) solve();
}