using namespace std;

#include <iostream>

#define MOD 1000000007

long long pow(long long a, long long b)  {
	long long res = 1; 
  	while(b > 0) {
		if (b % 2 == 1) { 
			res = (res * a) % MOD; 
		} 
		a = (a * a) % MOD; 
  		b >>= 1; 
	}
	return res; 
} 

long long N,K;

void solve() {
	cin >> N >> K;
	cout << pow(N,K) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}