using namespace std;

#include <iostream>

#define MAXN 200005

int N;
long long arr[MAXN],st[MAXN][19],logN[MAXN];

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

long long query(int L,int R) {
	int j = logN[R - L + 1];
	return gcd(st[L][j],st[R - (1 << j) + 1][j]);
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	for(int i = 2;i < N; i++) {
		logN[i] = logN[i >> 1] + 1;
	}
	for(int i = 1;i < N;++i) {
		st[i - 1][0] = abs(arr[i] - arr[i - 1]);
	}
	for(int j = 1;j < 19;j++) {
		for(int i = 0;i + (1 << j) <= N - 1;++i) {
			st[i][j] = gcd(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
		}
	}
	int ans = 0;
	for(int i = 0;i < N - 1;++i) {
		int l = i;
		int r = N - 2;
		while(l < r) {
			int m = (l + r + 1) >> 1;
			if(query(i,m) == 0 || query(i,m) > 1) {
				l = m;
			}else{
				r = m - 1;
			}
		}
		if(query(i,l) > 1 || query(i,l) == 0) ans = max(l - i + 1,ans);

	}
	cout << ans + 1 << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}