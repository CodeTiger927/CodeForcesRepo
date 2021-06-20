using namespace std;

#include <iostream>

int log2(int n) {
	int res = 0;
	while(n != 1) {
		res++;
		if(n & 1) return 0;
		n >>= 1;
	}
	return res;
}

void solve() {
	int N;
	cin >> N;
	if(log2(N)) {
		int l = log2(N);
		if(l & 1) {
			cout << "Bob" << endl;
		}else{
			cout << "Alice" << endl;
		}
	}else{
		if(N & 1) {
			cout << "Bob" << endl;
		}else{
			cout << "Alice" << endl;
		}
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}