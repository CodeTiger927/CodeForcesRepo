using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 100005

int N,arr[MAXN];
string s,s2;

void solve() {
	cin >> N >> s >> s2;
	for(int i = 0;i < N;++i) {
		arr[i] = (s[i] - '0') + (s2[i] - '0');
	}
	int mode = -1;
	int ans = 0;
	for(int i = 0;i < N;++i) {
		if(arr[i] == 1) {
			if(mode == 0) ans++;
			ans += 2;
			mode = -1;
		}else if(arr[i] == 0) {
			if(mode == 2) {
				ans += 2;
				mode = -1;
			}else if(mode == -1) {
				mode = 0;
			}else if(mode == 0) {
				mode = 0;
				ans += 1;
			}
		}else if(arr[i] == 2) {
			if(mode == 0) {
				ans += 2;
				mode = -1;
			}else if(mode == -1) {
				mode = 2;
			}
		}
	}
	if(mode == 0) ans++;
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}