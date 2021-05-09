using namespace std;

#include <iostream>
#include <cmath>

bool isSquare(long long x) {
	long long s = sqrt(x);
	return (s * s == x);
}

void solve() {
	long long N;
	cin >> N;
	if((N % 4 == 0 && isSquare(N)) || isSquare(2 * N)) {
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}