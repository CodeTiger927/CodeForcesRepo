using namespace std;

#include <iostream>

#define MAXN 1005

int N;
long long arr[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	long long ans = 0;
	for(int i = 0;i < N - 1;i += 2) {
		long long open = 0;
		long long m = arr[i];
		for(int j = i;j < N;++j) {
			if(j & 1) {
				if(arr[j] > open) {
					ans += min(m,arr[j] - (open - arr[i]));
				break;
				}else{
					ans += max(0ll,min(m - (open - arr[j]),arr[j]));
				}
				open -= arr[j];
				m = min(m,open + 1);
			}else{
				open += arr[j];
			}
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T = 1;
	// cin >> T;
	while(T--) solve();
}