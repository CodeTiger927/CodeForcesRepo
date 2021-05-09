using namespace std;

#include <iostream>
#include <set>

int N,W;

void solve() {
	cin >> N >> W;
	multiset<int> ms;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		ms.insert(cur);
	}
	int ans = 0;
	while(ms.size()) {
		int le = W;
		while(le > 0) {
			auto cur = ms.upper_bound(le);
			if(cur == ms.begin()) break;
			cur = prev(cur);
			le -= *cur;
			ms.erase(cur);
		}
		ans++;
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}