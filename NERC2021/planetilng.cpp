using namespace std;

#include <iostream>

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

int main() {
	long long N,a,b,c,d;
	cin >> N >> a >> b >> c >> d;
	long long area = abs(a * d - b * c);
	if(area != N) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	long long m = gcd(abs(a),abs(c));
	long long n = area / m;
	for(int i = 0;i < m;++i) {
		for(int j = 0;j < n;++j) {
			cout << i << " " << j << endl;
		}
	}
	return 0;
}