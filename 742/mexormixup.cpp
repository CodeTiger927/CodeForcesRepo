using namespace std;

#include <iostream>

#define MAXN 300005

int pref[MAXN],a,b;

void solve() {
	cin >> a >> b;
	if((pref[a - 1] ^ b) == 0) {
		cout << a << endl;
	}else if((pref[a - 1] ^ b) == a) {
		cout << a + 2 << endl;
	}else{
		cout << a + 1 << endl;
	}
	return;
}

int main() {
	for(int i = 1;i < MAXN;++i) {
		pref[i] = pref[i - 1] ^ i;
	}
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}