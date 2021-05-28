using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 50

int N;
const int largest = 11 * 111 - 11 - 111;
bool dp[largest + 5];

void solve() {
	cin >> N;
	if(N > largest) {
		cout << "YES" << endl;
		return;
	}
	cout << (dp[N] ? "YES" : "NO") << endl;
	return;
}

int main() {
	dp[0] = true;
	for(int i = 1;i <= largest;++i) {
		if(i >= 11) {
			dp[i] |= dp[i - 11];
		}
		if(i >= 111) {
			dp[i] |= dp[i - 111];
		}
	}
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}