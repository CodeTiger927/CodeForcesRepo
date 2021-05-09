using namespace std;

#include <iostream>
#include <cmath>
#include <iomanip>

#define MAXN 200005

int N;
long long K,x[MAXN],y[MAXN];

int main() {
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> x[i] >> y[i];
	}
	int j = N - 1;
	long double ans = 0;
	for(int i = N - 2;i >= 0;--i) {
		long long a = x[i + 1] - x[i], b = y[i + 1] - y[i];
		long long c = x[N - 1] - x[j], d = y[N - 1] - y[j] + K;
		long long e = x[N - 1] - x[i], f = y[N - 1] - y[i] + K;
		long long w = a * d - b * c;
		if(w >= 0) {
			long long n = a * f - b * e;
			long double len = sqrtl(a * a + b * b);
			if(n == 0) {
				ans += len;
			}else{
				long double nxt = min(1.0l,(long double)(d * e - c * f) / w);
				if(nxt >= 0) {
					ans += len * min(1.0l,(long double)(d * e - c * f) / w);
					j = i;
				}
			}
		}
	}
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}