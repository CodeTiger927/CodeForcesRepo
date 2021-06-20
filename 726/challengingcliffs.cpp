using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 200005

int N,arr[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	if(N == 2) {
		cout << arr[0] << " " << arr[1] << endl;
		return;
	}
	int gap = 2e9;
	int best = 0;
	for(int i = 0;i < N - 1;++i) {
		if(arr[i + 1] - arr[i] < gap) {
			gap = arr[i + 1] - arr[i];
			best = i;
		}
	}
	for(int i = best + 1;i < N;++i) {
		cout << arr[i] << " ";
	}
	for(int i = 0;i <= best;++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}