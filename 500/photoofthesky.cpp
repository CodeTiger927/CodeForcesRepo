using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 200005

int N;
long long arr[MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < 2 * N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + 2 * N);
	long long ans = (arr[N - 1] - arr[0]) * (arr[2 * N - 1] - arr[N]);
	for(int i = 1;i < N;++i) {
		long long cur = (arr[2 * N - 1] - arr[0]) * (arr[i + N - 1] - arr[i]);
		ans = min(ans,cur);
	}
	cout << ans << endl;
	return 0;
}