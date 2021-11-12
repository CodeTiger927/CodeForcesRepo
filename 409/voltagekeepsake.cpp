using namespace std;

#include <iostream>
#include <iomanip>

#define MAXN 100005

int N;
long double P,a[MAXN],b[MAXN],l,r;

int main() {
	cin >> N >> P;
	for(int i = 0;i < N;++i) {
		cin >> a[i] >> b[i];
	}
	r = 1e15;
	for(int it = 0;it < 100;++it) {
		long double m = (l + r) / 2;
		long double cur = 0;
		for(int i = 0;i < N;++i) {
			if(a[i] * m > b[i]) {
				cur += (a[i] * m - b[i]);
			}
		}
		if(cur / P / m <= 1 + 1e-13) {
			l = m;
		}else{
			r = m;
		}
	}
	if(r == 1e15) {
		cout << -1 << endl;
	}else{
		cout << setprecision(10) << fixed << l << endl;
	}
	return 0;
}