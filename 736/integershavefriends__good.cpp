using namespace std;

#include <iostream>

#define MAXN 105

int N;
long long arr[MAXN];

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	int ans = 1;
	for(int i = 0;i < N;++i) {
		for(int j = i;j < N;++j) {
			long long m = 2;
			for(int k = i;k <= j;++k) {
				m = max(m,arr[k] + 1);
			}
			for(int k = 2;k <= m;++k) {
				int all = arr[i] % k;
				bool flag = true;
				for(int l = i;l <= j;++l) {
					if(arr[l] % k != all) {
						flag = false;
						break;
					}
				}
				if(flag) {
					ans = max(ans,j - i + 1);
				}
			}
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}