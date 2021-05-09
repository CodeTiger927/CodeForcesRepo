using namespace std;

#include <iostream>
#include <math.h>

int N;

void solve() {
	cin >> N;
	bool yn = false;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		int s = sqrt(cur);
		if(s * s != cur) yn = true;
	}
	cout << (yn ? "YES" : "NO") << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}