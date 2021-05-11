using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 82

int N,M,K;
vector<int> v;
int dp[MAXN][MAXN][MAXN * MAXN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for(int i = 1;i <= N;++i) {
		int x;
		cin >> x;
		if(x) v.push_back(i);
	}
	v.push_back(++N);
	M = v.size();
	K = (N - 1) * (N - 2) / 2;

	memset(dp,0xcf,sizeof(dp));

	dp[0][0][0] = 0;
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < min(i,M);++j) {
			for(int k = 0;k + abs(i - v[j]) <= K;++k) {
				for(int a = 0;a < i;++a) {
					int &cur = dp[i][j + 1][k + abs(i - v[j])];
					cur = max(cur,dp[a][j][k] + (i - a - 1) * (a - j));
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0;i <= K;++i) {
		ans = max(ans,dp[N][M][i]);
		cout << ans << " ";
	}
	cout << endl;
	return 0;
}