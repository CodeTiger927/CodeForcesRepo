using namespace std;

#include <iostream>

#define MAXN 500005

int dp[MAXN],fre[MAXN],lb[MAXN],rb[MAXN],N,arr[MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		rb[arr[i]] = i;
	}
	for(int i = N - 1;i >= 0;--i) {
		lb[arr[i]] = i;
	}
	for(int i = N - 1;i >= 0;--i) {
		fre[arr[i]]++;
		dp[i] = dp[i + 1];
		if(i == lb[arr[i]]) {
			dp[i] = max(dp[i],fre[arr[i]] + dp[rb[arr[i]] + 1]);
		}else{
			dp[i] = max(dp[i],fre[arr[i]]);
		}
	}
	cout << (N - dp[0]) << endl;
}