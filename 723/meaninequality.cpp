using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 50

int N,arr[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < 2 * N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + 2 * N);
	for(int i = 0;i < N;++i) {
		cout << arr[i] << " " << arr[2 * N - 1 - i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}