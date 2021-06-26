using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 100005

int N;
long long arr[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) cin >> arr[i];
	sort(arr,arr + N);
	long long ans = arr[N - 1];
	long long sum = 0;
	for(int i = 0;i < N;++i) {
		ans -= arr[i] * i - sum;
		sum += arr[i];
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}