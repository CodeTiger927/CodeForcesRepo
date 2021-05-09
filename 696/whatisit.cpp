using namespace std;

#include <iostream>
#include <vector>

void solve() {
	int n;
	cin >> n;
	if(n == 1) {
		cout << 0 << endl;
		cout << 1 << endl;
		cout << 0 << endl;
		return;
	}

	long long ans = 0;
	long long cnt = 1;
	long long cur = n - 1;
	long long left = 0;
	while(left < n - 1) {
		if(cnt == 0) {
			cnt = 2;
			cur--;
		}
		ans += cur * cur;
		cnt--;
		left++;
	}
	cout << ans << endl;

	vector<int> v;
	vector<pair<int,int>> ops;
	cout << (n / 2 + 1) << " ";
	for(int i = 1;i < n / 2;++i) {
		cout << i << " ";
	}
	for(int i = n / 2 + 2;i <= n;++i) {
		cout << i << " ";
	}
	cout << (n / 2) << endl;
	for(int i = n / 2 + 1;i < n;++i) {
		ops.push_back({i,1});
	}
	for(int i = n / 2;i > 1;--i) {
		ops.push_back({i,n});
	}
	ops.push_back({1,n});
	cout << ops.size() << endl;
	for(int i = 0;i < ops.size();++i) {
		cout << ops[i].first << " " << ops[i].second << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}