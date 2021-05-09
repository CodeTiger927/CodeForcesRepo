using namespace std;

#include <iostream>

#define MAXN 100005

int N,arr[MAXN],ele[MAXN],border[MAXN];

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		ele[i] = border[i] = 0;
	}
	int m = 0;
	int k = 0;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		ele[arr[i]]++;
		m = max(m,ele[arr[i]]);
		if(i > 0 && arr[i] == arr[i - 1]) {
			k++;
			border[arr[i]]++;
			border[arr[i - 1]]++;
		}
	}
	border[arr[0]]++;
	border[arr[N - 1]]++;
	if(m > (N + 1) / 2) {
		cout << -1 << endl;
		return;
	}
	m = 0;
	for(int i = 1;i <= N;++i) {
		m = max(m,border[i]);
	}
	int ans = k + max(0,m - (k + 2));
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}