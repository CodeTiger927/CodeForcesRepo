using namespace std;

#include <iostream>

#define MAXN 200005
#define MOD 998244353

int N;
long long arr[MAXN],prefA[MAXN],pref[MAXN];

long long getAlternate(int l,int r) {
	return prefA[r] + prefA[l - 1];
}

long long getP(int l,int r) {
	return pref[r] - pref[l - 1];
}

void solve() {
	long long ans = 0;
	cin >> N;
	for(int i = 1;i <= N;++i) cin >> arr[i];
	for(int i = 1;i <= N;++i) {
		prefA[i] = arr[i] - prefA[i - 1];
		pref[i] = arr[i] + pref[i - 1];
	}
	for(int i = 1;i < N - 1;++i) {
		ans += (getP(1,i) > getP(i + 1,N));
	}
	for(int i = -1;i <= 1;i += 2) {
		for(int j = -1;j <= 1;j += 2) {
			ans += i * arr[1] + j * arr[N] < getP(2,N - 1);
			for(int k = 2;k <= min(3,N - 1);++k) {
				for(int a = k,b = k;a < N - max(0,j);a += 2) {
					if(i * arr[1] + getP(2,a) + j * arr[N] < getP(a + 1,N - 1)) b = a;
					while(b >= k && i * arr[1] + getP(2,b - 1) + getAlternate(b,a) + j * arr[N] >= getP(a + 1,N - 1)) b -= 2;
					ans += b / 2 + (~i && k == 3 && getAlternate(1,a) + j * arr[N] < getP(a + 1,N - 1));
				}
			}
		}
		ans %= MOD;
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}