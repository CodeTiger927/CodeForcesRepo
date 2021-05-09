using namespace std;

#include <iostream>

#define MOD 1000000007

void solve() {
	long long N;
	cin >> N;
	long long ans = ((((N / 4) + 1) % MOD) * (((N / 2) - (N / 4) + 1) % MOD)) % MOD;
	cout << ans << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}