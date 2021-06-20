using namespace std;

#include <iostream>

void solve() {
	int N;
	cin >> N;
	int sum = 0;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		sum += cur - 1;
	}
	if(sum >= 0) {
		cout << abs(sum) << endl;
	}else{
		cout << 1 << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}