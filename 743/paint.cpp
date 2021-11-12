using namespace std;

#include <iostream>
#include <vector>

#define MAXN 3005

int N,arr[MAXN],dp[MAXN][MAXN];
vector<int> v[MAXN];

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) v[i].clear();
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		dp[i][i] = 0;
		v[arr[i]].push_back(i);
	}
	for(int k = 1;k < N;++k) {
		for(int i = 0;i < N;++i) {
			int j = i + k;
			if(j >= N) continue;
			dp[i][j] = dp[i + 1][j];
			for(int k : v[arr[i]]) {
				if(k > i && k <= j) {
					dp[i][j] = max(dp[i][j],1 + dp[i + 1][k - 1] + dp[k][j]);
				}
			}
		}
	}
	cout << (N - 1 - dp[0][N - 1]) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}