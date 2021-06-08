using namespace std;

#include <iostream>

void solve() {
	int N;
	cin >> N;
	long long n = 1;
	while(2 * n <= N) n <<= 1;
	cout << (n - 1) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}