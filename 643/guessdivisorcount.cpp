using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 1005

long long N = 1000,M = 1e9,K = 1e18;
// long long target = 4194304;
vector<long long> p,v;
bool notP[MAXN];

long long qry(long long x) {
	cout << "? " << x << endl;
	long long res;
	cin >> res;
	// long long res = __gcd(target,x);
	return res;
}

void solve() {
	long long x = 1;
	v.clear();
	for(long long i = 0,j = 1;i < p.size() && (~-j || max(4ll,x) * p[i] * p[i] * p[i] <= M);++i) {
		j *= p[i];
		if(i == p.size() - 1 || p[i + 1] > K / j) {
			j = qry(j);
			for(int l = i;~-j;l--) {
				if(!(j % p[l])) {
					v.push_back(p[l]);
					j /= p[l];
					x *= p[l];
				}
			}
		}
	}

	long long ans = 2;
	for(long long i = 0,j = 1;i < v.size();++i) {
		long long y = 1;
		while(x * y <= M) y *= v[i];
		j *= y;
		if(i == v.size() - 1 || M * v[i + 1] / x > K / j) {
			j = qry(j);
			for(int l = i;~-j;--l) {
				long long cnt = 1;
				while(!(j % v[l])) {
					j /= v[l];
					cnt++;
				}
				ans *= cnt;
				x /= v[l];
			}
		}
	}
	ans = max(ans,8ll);
	cout << "! " << ans << endl;
	return;
}

int main() {
	for(int i = 2;i < N;++i) {
		if(!notP[i]) {
			p.push_back(i);
			for(int j = i * i;j < N;j += i) {
				notP[j] = true;
			}
		}
	}
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}