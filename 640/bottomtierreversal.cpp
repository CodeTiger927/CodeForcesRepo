using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 3005

int N,arr[MAXN],ind[MAXN];
vector<int> ans;

void move(int x) {
	for(int i = 1;i <= (x / 2);++i) {
		swap(arr[i],arr[x + 1 - i]);
		swap(ind[arr[i]],ind[arr[x + 1 - i]]);
	}
	ans.push_back(x);
}

void solve() {
	cin >> N;
	ans.clear();
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		ind[arr[i]] = i;
	}
	for(int i = 1;i <= N;++i) {
		if(i % 2 != arr[i] % 2) {
			cout << -1 << endl;
			return;
		}
	}
	for(int i = N;i >= 1;--i) {
		if(i & 1) {
			if(ind[i] != 1) {
				move(ind[i]);
			}
		}else{
			if(ind[i] == 2) {
				move(i + 1);
				continue;
			}
			move(ind[i] - 1);
			move(ind[i] + 1);
			move(3);
			move(i + 1);
		}
	}
	// for(int i = 1;i <= N;++i) {
	// 	cout << arr[i] << " \n"[i == N];
	// }
	// for(int i = 1;i <= N;++i) {
	// 	cout << ind[i] << " \n"[i == N];
	// }
	// if(ans.size() > (5 * N / 2)) {
	// 	cout << "RIP" << endl;
	// }
	cout << ans.size() << endl;
	for(int i = 0;i < ans.size();++i) {
		cout << ans[i] << " \n"[i == ans.size() - 1];
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}