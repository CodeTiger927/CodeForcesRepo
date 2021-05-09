using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 100005

int N,arr[MAXN],pre[MAXN],dp[MAXN],pref[MAXN];

int main() {
	cin >> N;
	memset(pre,-1,sizeof(pre));
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	int ptr = 1;
	for(int i = 1;i < N;++i) {
		if(arr[i] != arr[i - 1]) {
			arr[ptr++] = arr[i];
		}
	}
	dp[0] = 0;
	dp[1] = 1;
	int ans = ptr;
	pre[arr[0]] = 1;
	for(int i = 2;i <= ptr;++i) {
		int tmp = pre[arr[i - 1]] + 1;
		dp[i] = min(dp[i - 1] + (arr[i - 1] != arr[i - 3]),(tmp == 0 ? N : dp[tmp]) + (i - tmp - 1) + (tmp >= 2 && arr[i - 1] != arr[tmp - 2]));
		pre[arr[i - 1]] = i;
		ans = min(ans,dp[i] + ptr - i);
	}
	cout << ans << endl;
	return 0;
}