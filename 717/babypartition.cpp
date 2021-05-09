using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 105

int N,arr[MAXN],cnt[MAXN];
bool dp[MAXN][200005];
long long sum;

int main() {
	sum = 0;
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		sum += arr[i];
	}
	if(sum % 2 == 1) {
		cout << 0 << endl;
		return 0;
	}
	dp[0][0] = true;
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < 200005;++j) {
			dp[i][j] = dp[i - 1][j];
			if(j - arr[i] >= 0 && dp[i - 1][j - arr[i]]) {
				dp[i][j] = true;
			}
		}
	}
	if(!dp[N][sum / 2]) {
		cout << 0 << endl;
		return 0;
	}
	for(int i = 0;i < 15;++i) {
		for(int j = 1;j <= N;++j) {
			if(arr[j] % 2 == 1) {
				cout << 1 << endl;
				cout << j << endl;
				return 0;
			}else{
				arr[j] = arr[j] / 2;
			}
		}
	}
	return 0;
}