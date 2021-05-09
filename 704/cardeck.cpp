using namespace std;

#include <iostream>
#include <vector>

#define MAXN 100005

int N,arr[MAXN],rev[MAXN];

void solve() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		rev[arr[i]] = i;
	}
	int cur = N;
	vector<int> ans;
	for(int i = N;i > 0;--i) {
		if(rev[i] > cur) continue;
		for(int j = rev[i];j < cur;++j) {
			cout << arr[j] << " ";
		}
		cur = rev[i];
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