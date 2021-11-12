using namespace std;

#include <iostream>
#include <cstring>

string str;

void solve() {
	cin >> str;
	int ans = 10;
	int l = 0;
	int r = 0;
	for(int i = 0;i < 10;++i) {
		if(str[i] != '0' && (i % 2 == 0)) {
			l++;
		}else if(str[i] == '1') {
			r++;
		}
		int maxL = l + (9 - i) / 2;
		int maxR = r + (10 - i) / 2;
		// cout << l << " " << r << " " << maxL << " " << maxR << endl;
		if(maxL < r || maxR < l) {
			ans = min(ans,i + 1);
			break;
		}
	}
	l = 0;
	r = 0;
	for(int i = 0;i < 10;++i) {
		if(str[i] != '0' && (i % 2 == 1)) {
			r++;
		}else if(str[i] == '1') {
			l++;
		}
		int maxL = l + (9 - i) / 2;
		int maxR = r + (10 - i) / 2;
		if(maxL < r || maxR < l) {
			ans = min(ans,i + 1);
			break;
		}
	}
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}