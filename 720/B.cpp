using namespace std;

#include <iostream>
#include <vector>
#include <array>
#include <assert.h>
#include <algorithm>

#define MAXN 200005

long long N,arr[MAXN];

void solve() {
	cin >> N;
	vector<array<long long,4>> ans;
	long long flag = 0;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		if(i > 0) {
			long long m = min(arr[i],arr[i - 1]);
			ans.push_back({i,i + 1,(2000000000 - i),m});
			arr[i - 1] = (2000000000 - i);
			arr[i] = m;
		}
	}

	while(__gcd(arr[N - 2] - flag,arr[N - 1]) != 1ll) {
			flag++;
	}
	assert(ans.size() <= N);
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();++i) {
		assert((ans[i][2] - flag) <= 2e9);
		cout << ans[i][0] << " " << ans[i][1] << " " << (ans[i][2] - flag) << " " << ans[i][3] << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}