using namespace std;

#include <iostream>

#define MAXN 5005

int N,arr[MAXN];
int dp[MAXN][MAXN],pre[MAXN][MAXN];

int main() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i <= N;++i) {
		for(int j = 0;j <= N;++j) {
			dp[i][j] = pre[i][j] = 1e9;
		}
	}
	dp[0][0] = pre[0][0] = 0;
	// dp[i][j] = first i hills, j 
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j <= N;++j) {
			if(i == 0 && j == 0) dp[i][j] = 0;
			if(i == 1 && j == 1) {
				dp[i][j] = min(dp[i][j],max(arr[i + 1] + 1 - arr[i],0));
			}else if(j == 1) {
				dp[i][j] =  min(dp[i][j],max(arr[i - 1] + 1 - arr[i],0) + max(arr[i + 1] + 1 - arr[i],0));
			}
			if(i >= 3) dp[i][j] = min(dp[i][j],pre[i - 3][j - 1] + max(arr[i - 1] + 1 - arr[i],0) + max(arr[i + 1] + 1 - arr[i],0));
			if(i >= 3) dp[i][j] = min(dp[i][j],dp[i - 2][j - 1] + max(min(arr[i - 1],arr[i - 2] - 1) + 1 - arr[i],0) + max(arr[i + 1] + 1 - arr[i],0));
			pre[i][j] = min(pre[i - 1][j],dp[i][j]);
		}
	}
	for(int i = 1;i <= (N + 1) / 2;++i) {
		cout << pre[N][i] << " ";
	}
	cout << endl;
	return 0;
}