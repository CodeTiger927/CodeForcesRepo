using namespace std;

#include <iostream>

void solve() {
	int a,b;
	cin >> a >> b;
	if(abs(a - b) & 1) {
		cout << -1 << endl;
		return;
	}
	if(a == 0 && b == 0) {
		cout << 0 << endl;
	}else if(a == -b || a == b) {
		cout << 1 << endl;
	}else{
		cout << 2 << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}