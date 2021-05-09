using namespace std;

#include <iostream>
#include <math.h>

#define MAXN 20000005

int spf[MAXN];

void sieve() {
	for(int i = 1;i < MAXN;i++) {
		spf[i] = i;
	}
	for(int i = 4;i < MAXN;i += 2) {
		spf[i] = 2;
	}
	for(int i = 3;i * i < MAXN;i++) {
		if(spf[i] == i) {
			for(int j = i * i;j < MAXN;j += i) {
				if(spf[j] == j) spf[j] = i;
			}
		}
	}
	return;
}

long long C,D,X;

long long examine(long long m) {
	long long res = 1;
	if(X % m != 0) return 0;
	long long x = X / m + D;
	if(x % C != 0) return 0;
	long long y = x / C;
	while(y != 1) {
		long long cur = spf[y];
		while(spf[y] == cur) {
			y /= cur;
		}
		res <<= 1;
	}
	return res;
}

void solve() {
	cin >> C >> D >> X;
	long long ans = 0;
	for(int i = 1;i <= sqrt(X);++i) {
		if(X % i == 0) {
			ans += examine(i);
			if(i != X / i) {
				ans += examine(X / i);
			}
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	sieve();
	int T;
	cin >> T;
	while(T--) solve();
}