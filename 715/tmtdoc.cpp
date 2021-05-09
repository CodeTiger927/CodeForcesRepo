using namespace std;

#include <iostream>
#include <cstring>
#include <vector>

int N,cnt;
string str;

void solve() {
	cnt = 0;
	cin >> N >> str;
	for(int i = 0;i < N;++i) {
		if(str[i] == 'M') {
			cnt++;
		}
	}
	
	if(3 * cnt != N) {
		cout << "NO" << endl;
		return;
	}
	
	int cnt1 = 0;
	for(int i = 0;i < N;++i) {
		if(str[i] == 'M') {
			if(2 * cnt1 < (i + 1)) {
				cout << "NO" << endl;
				return;
			}
		}else{
			cnt1++;
		}
	}
	cnt1 = 0;
	for(int i = N - 1;i >= 0;--i) {
		if(str[i] == 'M') {
			if(2 * cnt1 < (N - i)) {
				cout << "NO" << endl;
				return;
			}
		}else{
			cnt1++;
		}
	}
	cout << "YES" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}