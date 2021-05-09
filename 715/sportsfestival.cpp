using namespace std;

#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 2005

int N;
long long dp[MAXN][MAXN],arr[MAXN];

long long solve(int a,int b) {
	if(dp[a][b] != -1) return dp[a][b];
	if(a == b) {
		return dp[a][b] = 0;
	}
	dp[a][b] = min(solve(a,b - 1),solve(a + 1,b)) + arr[b] - arr[a];
	return dp[a][b];
}

int main() {
	memset(dp,-1,sizeof(dp));
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	cout << solve(0,N - 1) << endl;
}