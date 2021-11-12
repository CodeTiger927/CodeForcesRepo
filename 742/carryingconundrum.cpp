using namespace std;

#include <iostream>
#include <cstring>

string s;

void solve() {
	cin >> s;
	int s1 = 0;
	int s2 = 0;
	int pow = 1;
	for(int i = s.size() - 1;i >= 0;--i) {
		if(i & 1) {
			s1 += (s[i] - '0') * pow;
		}else{
			s2 += (s[i] - '0') * pow;
		}
		if((s.size() - i) % 2 == 0) pow *= 10;
	}
	long long ans = (s1 + 1) * (s2 + 1) - 2;
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}