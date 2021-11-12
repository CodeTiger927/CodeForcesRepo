using namespace std;

#include <iostream>
#include <cstring>

int N;
string s;

void solve() {
	cin >> N >> s;
	string ans = "";
	for(int i = 0;i < N;++i) {
		if(s[i] == 'U') {
			ans += 'D';
		}else if(s[i] == 'D') {
			ans += 'U';
		}else if(s[i] == 'L' || s[i] == 'R') {
			if(ans.size() == 0 || ans[ans.size() - 1] != 'L') {
				ans += 'L';
			}else{
				ans += 'R';
			}
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}