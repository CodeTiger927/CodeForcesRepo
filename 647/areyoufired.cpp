using namespace std;

#include <iostream>

#define MAXN 500005

int N,M;
long long arr[MAXN],m[MAXN],x;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	M = (N + 1) >> 1;
	for(int i = 0;i < M;++i) cin >> arr[i];
	cin >> x;
	long long pref = 0;
	for(int i = 1;i <= M;++i) {
		pref += x - arr[i - 1];
		m[i] = min(m[i - 1],pref);
	}
	pref = 0;
	for(int i = 1;i <= M;++i) {
		pref += arr[i - 1];
	}
	for(int i = M;i <= N;++i) {
		if(pref + m[N - i] > 0) {
			cout << i << endl;
			return 0;
		}
		pref += x;
	}
	cout << -1 << endl;
	return 0;
}