using namespace std;

#include <iostream>
#include <math.h>

long long powt[10],sum,N;

long long get(long long n,long long k) {
	return powt[k];
}

void solve() {
	cin >> sum >> N;
	for(int i = 0;i < N;++i) {
		long long cur = sum - (N - i - 1);
		if(i != N - 1) {
			cur = get(cur,log10(cur));
		}
		cout << cur << " \n"[i == N - 1];
		sum -= cur;
	}
	return;
}

int main() {
	powt[0] = 1;
	for(int i = 1;i < 10;++i) powt[i] = powt[i - 1] * 10;
	int T;
	cin >> T;
	while(T--) solve();
}