using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 200005

int N,K,a[MAXN],b[MAXN],c[MAXN],cc[MAXN],dp[MAXN],dpf[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		b[i] = a[i];
		c[i] = cc[i] = dp[i] = dpf[i] = 0;
	}
	sort(b,b + N);
	K = unique(b,b + N) - b;
	for(int i = 0;i < N;++i) {
		c[a[i] = lower_bound(b,b + K,a[i]) - b]++;
	}
	for(int i = 0;i < N;++i) {
		if(!(cc[a[i]]++) && a[i]) {
			if(c[a[i] - 1] == cc[a[i] - 1]) {
				dp[a[i]] = dp[a[i] - 1];
			}else{
				dp[a[i]] = cc[a[i] - 1];
				dpf[a[i]] = dp[a[i]];
			}
		}
		if(a[i]) {
			if(c[a[i] - 1] == cc[a[i] - 1]) {
				dpf[a[i]] = max(dpf[a[i]],dp[a[i] - 1]);
			}else{
				dpf[a[i]] = max(dpf[a[i]],cc[a[i] - 1]);
			}
		}
		dp[a[i]]++;
		dpf[a[i]]++;
	}
	cout << (N - *max_element(dpf,dpf + K)) << endl;
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