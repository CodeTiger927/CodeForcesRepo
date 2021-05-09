using namespace std;

#include <iostream>

int N,K;

void solve() {
	cin >> N >> K;
	if(K > (N - 1) / 2) {
		cout << -1 << endl;
		return;
	}
	int l = 2;
	int r = N;
	cout << 1 << " ";
	for(int i = 0;i < K;++i) {
		cout << r-- << " " << l++ << " ";
	}
	for(int i = l;i <= r;++i) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}