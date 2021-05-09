using namespace std;

#include <iostream>

#define INF 1e18

long long N,K,a,b;

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

int main() {
	long long ansX = INF;
	long long ansY = 0;
	cin >> N >> K >> a >> b;
	for(int i = 0;i <= N;++i) {
		long long sa = 1ll + a;
		long long ga = 1ll + K - a;
		long long sb = 1ll + b + i * K;
		long long gb = 1ll + K - b + i * K;

		// small small
		if(sb > sa && sb - sa <= N * K) {
			ansX = min(ansX,(N * K) / gcd(N * K,sb - sa));
			ansY = max(ansY,(N * K) / gcd(N * K,sb - sa));
		}

		// small large
		if(gb > sa && gb - sa <= N * K) {
			ansX = min(ansX,(N * K) / gcd(N * K,gb - sa));
			ansY = max(ansY,(N * K) / gcd(N * K,gb - sa));
		}
		// large small
		 if(sb > ga && sb - ga <= N * K) {
			ansX = min(ansX,(N * K) / gcd(N * K,sb - ga));
			ansY = max(ansY,(N * K) / gcd(N * K,sb - ga));
		}
		// large large
		 if(gb > ga && gb - ga <= N * K) {
			ansX = min(ansX,(N * K) / gcd(N * K,gb - ga));
			ansY = max(ansY,(N * K) / gcd(N * K,gb - ga));
		}
	}

	cout << ansX << " " << ansY << endl;
}