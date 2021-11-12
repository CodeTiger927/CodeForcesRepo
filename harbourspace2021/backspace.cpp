using namespace std;

#include <iostream>
#include <cstring>

int N,M;
string s,t;

void solve() {
	cin >> s >> t;
	N = s.length();
	M = t.length();
	int f0 = N;
	int f1 = N;
	for(int i = 0;i < N;++i) {
		if(s[i] == t[0]) {
			if(i & 1) {
				f1 = min(f1,i);
			}else{
				f0 = min(f0,i);
			}
		}
	}
	int l = 0;
	int r = 0;
	for(int i = 0;i < N;++i) {
		if(i > f0 && (i - f0) & 1 && l < M && s[i] == t[l + 1]) {
			f0 = i;
			l++;
		}
		if(i > f1 && (i - f1) & 1 && l < M && s[i] == t[r + 1]) {
			f1 = i;
			r++;
		}
	}
	if((l == M - 1 && (N - f0) % 2 == 1) || (r == M - 1 && (N - f1) % 2 == 1)) {
		cout << "YES" << endl;
	}else{
		cout << "NO" << endl;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}