using namespace std;

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <assert.h>
#include <cstring>

#define MAXN 505

int N,arr[MAXN],cop[MAXN];
vector<int> ans;

void cyclic_shift(int i) {
	ans.push_back(i + 1);
	rotate(arr + i,arr + i + 2,arr + i + 3);
	return;
}

void solve() {
	set<int> s;
	ans.clear();
	cin >> N;
	bool d = false;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		d |= s.count(arr[i]);
		s.insert(arr[i]);
	}
	
	for(int last = N - 1,i = 500;last >= 2;) {
		int ind = -1;
		for(int j = 0;j <= last;++j) {
			if(arr[j] == i) ind = j;
		}
		if(ind == -1) {
			i--;
			continue;
		}
		for(int j = ind;j <= last - 2;j += 2) {
			cyclic_shift(j);
			cyclic_shift(j);
		}
		while(arr[last] != i) cyclic_shift(last - 2);
		last--;
	}
	if(arr[0] > arr[1]) {
		if(!d) {
			cout << -1 << "\n";
			return;
		}
		int cur = 0;
		for(int i = 0;i < N;++i) {
			cop[i] = arr[i];
		}
		bool flag = false;
		for(int i = 0;i < 3;++i) {
			if((arr[cur] <= arr[cur + 1] && arr[cur + 1] <= arr[cur + 2])) {
				flag = true;
				break;
			}
			cyclic_shift(0);
		}
		if(!flag) {
			while(cop[cur + 1] != cop[cur + 2]) {
				cyclic_shift(cur);
				cyclic_shift(cur++);
			}
			while(!(arr[cur] <= arr[cur + 1] && arr[cur + 1] <= arr[cur + 2])) cyclic_shift(cur);
		}
	}
	cout << ans.size() << endl;
	for(auto x : ans) cout << x << " ";
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}