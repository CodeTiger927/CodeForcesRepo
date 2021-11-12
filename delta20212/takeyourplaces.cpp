using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

int N,arr[MAXN];

void solve() {
	vector<int> e,o;
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		if(arr[i] & 1) {
			e.push_back(i);
		}else{
			o.push_back(i);
		}
	}
	long long ans = 1e18;
	if(abs((int)o.size() - (int)e.size()) > 1) {
		cout << -1 << endl;
		return;
	}
	if(o.size() >= e.size()) {
		long long cur = 0;
		for(int i = 0;i < o.size();++i) {
			cur += abs(o[i] - 2ll * i);
		}
		ans = min(ans,cur);
	}
	if(e.size() >= o.size()) {
		long long cur = 0;
		for(int i = 0;i < e.size();++i) {
			cur += abs(e[i] - 2ll * i);
		}
		ans = min(ans,cur);
	}
	cout << (ans > 1e16 ? -1 : ans) << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}