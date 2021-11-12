using namespace std;

#include <iostream>
#include <cstring>

int N,l,r,cnt;
string s;

void solve() {
	cin >> s;
	N = s.size();
	cnt = 0;
	l = N;
	r = -1;
	for(int i = 0;i < N;++i) {
		if(s[i] == '0') {
			l = min(i,l);
			r = max(i,r);
			cnt++;
		}
	}
	if(r == -1) {
		cout << 0 << endl;
	}else if(r - l + 1 == cnt) {
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
	return 0;
}