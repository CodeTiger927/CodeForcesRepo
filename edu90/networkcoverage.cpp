using namespace std;

#include <iostream>

#define MAXN 3000005

int N;
long long a[MAXN],b[MAXN],p[MAXN],q[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) cin >> a[i];
	for(int i = 0;i < N;++i) cin >> b[i];
	for(int i = 0;i < 3 * N;++i) p[i + 1] = p[i] + a[i % N];
	for(int i = 0;i < 3 * N;++i) q[i + 1] = q[i] + b[i % N];
	long long v = q[0] - p[1];
	long long e = 0;
	for(int i = 2;i < 3 * N;++i) {
		v = max(v,q[i - 2] - p[i - 1]);
		e = max(e,v + p[i] - q[i]);
	}
	cout << (e == 0 && q[N] >= p[N] ? "YES" : "NO") << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}