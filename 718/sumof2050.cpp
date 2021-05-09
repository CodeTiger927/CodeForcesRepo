using namespace std;

#include <iostream>
#include <cstring>

long long N;

void solve() {
	cin >> N;
	if(N % 2050 != 0) {
		cout << "-1" << endl;
		return;
	}
	N /= 2050;
	string s = to_string(N);
	long long ans = 0;
	for(int i = 0;i < s.length();++i) {
		ans += (s[i] - '0');
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}