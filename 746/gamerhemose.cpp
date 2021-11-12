using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 200005

int N,M,arr[MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	long long x = arr[N - 1];
	long long y = arr[N - 2];
	long long z = x + y;
	long long ans = min(((M - 1) / z + 1) * 2,((M - x - 1) / z + 1) * 2 + 1);
	if(M <= x) {
		cout << 1 << endl;
	}else{
		cout << ans << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}