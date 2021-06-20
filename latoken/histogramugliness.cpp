using namespace std;

#include <iostream>

#define MAXN 400005

int N;
long long arr[MAXN];

void solve() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
	}
	arr[N + 1] = 0;
	long long sum = 0;
	for(int i = 1;i <= N;++i) {
		if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
			int cur = max(arr[i - 1],arr[i + 1]); sum += arr[i] - cur;
			arr[i] = cur;
		}
	}
	for(int i = 1;i <= N + 1;++i) {
		sum += abs(arr[i] - arr[i - 1]);
	}
	cout << sum << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}