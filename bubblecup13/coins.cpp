using namespace std;

#include <iostream>

int N,K;
long long total,total2;

int main() {
	cin >> N >> K;
	for(int i = 0;i < K;++i) {
		long long a,b;
		cin >> a >> b;
		total += a * b;
		total2 += b;
	}
	if(total2 < N) {
		cout << 1 << endl;
	}else if(total2 > N) {
		cout << -1 << endl;
	}else{
		cout << (2 * (total % N == ((1ll * N * (N - 1) / 2)) % N) - 1) << endl;
	}
	return 0;
}