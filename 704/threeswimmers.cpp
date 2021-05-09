using namespace std;

#include <iostream>
#include <algorithm>

long long nxt(long long p,long long x) {
	return ((p - 1) / x + 1) * x;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		long long p,a,b,c;
		cin >> p >> a >> b >> c;
		cout << min({nxt(p,a),nxt(p,b),nxt(p,c)}) - p << endl;
	}
}