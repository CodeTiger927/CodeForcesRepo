using namespace std;

#include <iostream>

#define MAXN 200005

int N,K,M,arr[MAXN];

void solve() {
	cin >> N >> K >> M;
	int m = (K - 1) >> 1;
	for(int i = 0;i < M;++i) {
		cin >> arr[i];
	}
	if((N - M) % (K - 1) != 0) {
		cout << "NO" << endl;
		return;
	}
	bool ans = false;
	for(int i = 0;i < M;++i) {
		if(arr[i] - i - 1 >= m && N - arr[i] - (M - i - 1) >= m) {
			ans = true;
		}
	}
	if(ans) {
		 cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}