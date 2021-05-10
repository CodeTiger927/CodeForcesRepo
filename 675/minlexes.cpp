using namespace std;

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 100005

int N,dp[MAXN],p[MAXN];
string s,ss,ans[MAXN];
bool popLast = false;

int main() {
	cin >> s;
	N = s.length();
	for(int i = N - 1;i >= 0;--i) {
		if(ss.length() == 0) {
			ss += s[i];
			popLast = false;
		}else if(ss.back() == s[i]) {
			if(!popLast && p[i + 1] <= s[i]) {
				p[i] = p[i + 2];
				ss.pop_back();
				popLast = true;
			}else{
				p[i] = p[i + 1];
				ss += s[i];
				popLast = false;
			}
		}else{
			p[i] = ss.back();
			ss += s[i];
			popLast = false;
		}
		dp[i] = ss.size();
		if(ss.size() <= 10) {
			ans[i] = ss;
		}else{
			ans[i] = ss.substr(0,2) + "..." + ss.substr(ss.size() - 5,5);
		}
		reverse(ans[i].begin(),ans[i].end());
	}
	for(int i = 0;i < N;++i) {
		cout << dp[i] << " " << ans[i] << endl;
	}
	return 0;
}