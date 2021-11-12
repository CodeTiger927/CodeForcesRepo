using namespace std;

#include <iostream>

long long N,S;

void solve() {
	cin >> N >> S;
	long long n = (N + 2) / 2;
	long long ans = S / n;
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}