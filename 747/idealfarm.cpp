using namespace std;

#include <iostream>

int T;
long long S,N,K;

void solve() {
	cin >> S >> N >> K;
	if(S == K) {
		cout << "YES" << endl;
		return;
	}else if(S < K) {
		cout << "NO" << endl;
		return;
	}
	long long r = S;
	long long l = S - K + 1;
	long long sz = r - l + 1;
	long long k = (S / K) * K;
	long long b = r - k + 1;
	long long a = sz - b;
	long long cnt = S + K;
	cnt -= ((S / K) & 1) ? b : a;
	cout << ((2 * N + 1 > cnt) ? "YES" : "NO") << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	while(T--) solve();
	return 0;
}