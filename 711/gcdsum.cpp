using namespace std;

#include <iostream>
#include <algorithm>

long long N;

bool test(long long x) {
	long long y = x;
	long long sum = 0;
	while(x) {
		sum += x % 10;
		x /= 10;
	}
	return (__gcd(sum,y) > 1);
}

void solve() {
	cin >> N;
	while(!test(N)) {
		N++;
	}
	cout << N << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}