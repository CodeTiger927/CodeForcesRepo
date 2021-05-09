using namespace std;

#include <iostream>

#define MAXN 200005
#define MOD 1000000007

int N,arr[MAXN];

void solve() {
	cin >> N;
	int all;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		if(i == 0) all = arr[0];
		all &= arr[i];
	}
	long long cnt = 0;
	for(int i = 0;i < N;++i) {
		if(arr[i] == all) cnt++;
	}
	if(cnt < 2) {
		cout << 0 << endl;
		return;
	}
	long long ans = (cnt * (cnt - 1)) % MOD;
	for(int i = 1;i <= N - 2;++i) {
		ans = (ans * i) % MOD;
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}