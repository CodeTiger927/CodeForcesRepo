using namespace std;

#include <iostream>
#include <deque>

#define MAXN 55
#define MAXK 20005

int N,M,K,a[MAXN][MAXK],dp[MAXN][MAXK],pre[MAXN][MAXK],pre2[MAXN][MAXK],suf2[MAXN][MAXK];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for(int i = 1;i <= N;++i) {
		for(int j = 1;j <= M;++j) {
			cin >> a[i][j];
			pre[i][j] = pre[i][j - 1] + a[i][j];
		}
	}
	for(int i = 1;i <= M;++i) {
		dp[1][i] = pre[1][min(M,i + K - 1)] - pre[1][i - 1];
		pre2[1][i] = max(pre2[1][i - 1],dp[1][i] + pre[2][min(M,i + K - 1)] - pre[2][i - 1]);
	}
	for(int i = M;i >= 1;--i) suf2[1][i] = max(suf2[1][i + 1],dp[1][i] + pre[2][min(M,i + K - 1)] - pre[2][i - 1]);
	for(int i = 2;i <= N;++i) {
		deque<int> q;
		for(int j = 1;j <= M;++j) {
			dp[i][j] = max(pre2[i - 1][max(j - K,0)],suf2[i - 1][min(M + 1,j + K)]);
			while(!q.empty() && q.front() < j - K + 1) q.pop_front();
			while(!q.empty() && dp[i - 1][j] > pre[i][j - 1] - pre[i][q.back() - 1] + dp[i - 1][q.back()]) q.pop_back();
			q.push_back(j);
			dp[i][j] = max(dp[i][j],pre[i][j - 1] - pre[i][q.front() - 1] + dp[i - 1][q.front()]);
		}
		q.clear();
		for(int j = M;j >= 1;--j) {
			while(!q.empty() && q.front() > j + K - 1) q.pop_front();
			while(!q.empty() && dp[i - 1][j] > pre[i][min(q.back() + K - 1,M)] - pre[i][min(j + K - 1,M)] + dp[i - 1][q.back()]) q.pop_back();
			q.push_back(j);
			dp[i][j] = max(dp[i][j],pre[i][min(q.front() + K - 1,M)] - pre[i][min(j + K - 1,M)] + dp[i - 1][q.front()]);
			dp[i][j] += pre[i][min(M,j + K - 1)] - pre[i][j - 1];
			suf2[i][j] = max(suf2[i][j + 1],dp[i][j] + pre[i + 1][min(M,j + K - 1)] - pre[i + 1][j - 1]);
		}
		for(int j = 1;j <= M;++j) pre2[i][j] = max(pre2[i][j - 1],dp[i][j] + pre[i + 1][min(M,j + K - 1)] - pre[i + 1][j - 1]);
	}
	cout << pre2[N][M] << endl;
	return 0;
}